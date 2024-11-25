#!/usr/bin/env python3
import pycparser
from pycparser import c_ast, parse_file, c_generator, c_parser
from pycparser.c_ast import FuncCall, Constant, ExprList

import re
import os
import sys

class FunctionTransformer(c_ast.NodeVisitor):
    def __init__(self):
        self.transformed_code = []
        self.generator = c_generator.CGenerator()
        self.fun_args = 101
        self.transformed_funcs = []

    def nonvisit(self, ast):
        for node in ast.ext:
            if isinstance(node, c_ast.Decl) and isinstance(node.type, c_ast.FuncDecl):
                code = generator.visit(ext) + ';'
                print(code)

            elif isinstance(node, c_ast.FuncDef):
                continue

            else:

                code = self.generator.visit(node)
                if code:
                    if isinstance(node, (c_ast.Decl, c_ast.Typedef)):
                        code += ';'
                    print(code)
                else:
                    print(node)

    def visit_FuncDef(self, node):
        func_name = node.decl.name
#        print(node.decl.type) # TODO: Use this to get the type and print it, too
        params = node.decl.type.args.params if node.decl.type.args else []

        if func_name == "main":
            transformed_func = f"if (fun_args == 100) {{ // {func_name}("
            self.transformed_funcs.append([func_name, 100])
            print(f"//Function Definition: {func_name}()  -->  main2(100)")
        else:
            transformed_func = f"if (fun_args == {self.fun_args}) {{ // {func_name}("
            self.transformed_funcs.append([func_name, self.fun_args])
            print(f"//Function Definition: {func_name}()  -->  main2({self.fun_args})")
            self.fun_args += 1

        arg_types = []

        for param in params:
            param_decl = self.generator.visit(param)
            transformed_func += f"{param_decl}, "

        transformed_func = transformed_func.rstrip(", ") + ")\n"

        for param in params:
            param_decl = self.generator.visit(param)
            for i in range(len(param_decl) - 1, -1, -1):
                if param_decl[i] == " ":
                    param_decl_short = param_decl[:i]
                    break
                elif param_decl[i] == "*":
                    param_decl_short = param_decl[:i+1]
                    break

            transformed_func += f"    {param_decl} = va_arg(args, {param_decl_short});\n"

        transformed_func += f"    va_end(args);\n"

        self.check_for_function_calls(node)

        func_body = self.generator.visit(node.body)

        remove_fb = lambda s: s[1:] if s and s[0] == '{' else s
        indented_body = remove_fb(func_body)
        remove_lb = lambda s: s[:-2] if s and s[-2] == '}' else s
        indented_body = remove_lb(indented_body)
        indented_body = ''.join(['  ' + line for line in indented_body.splitlines(True)])

        transformed_func += indented_body + "\n}"

        self.transformed_code.append(transformed_func)

    def check_for_function_calls(self, node):
        if isinstance(node, FuncCall):
            for transformed_func in self.transformed_funcs:
                if transformed_func[0] == node.name.name:
                    print(f"//Function Call: {node.name.name}()  -->  main2({transformed_func[1]})")
                    node.name.name = "main2"
                    if node.args:
                        args = node.args.exprs
                        new_args = [Constant('int', str(transformed_func[1]))]
                        new_args.extend(args)
                        node.args = ExprList(new_args)

                    break

        for child in node.children():
            self.check_for_function_calls(child[1])


def transform_c_file(file_path):
    ast = parse_file(file_path, use_cpp=True, cpp_path='cc',
                     cpp_args=['-E', '-std=c99', '-I../pycparser/utils/fake_libc_include/', '-I/usr/include'])

    transformer = FunctionTransformer()

    transformer.visit(ast)

    print("\n" * 3)

    for include in extract_includes(input_file):
        print(f"#include {include}")

    print("#include <stdarg.h>")

    transformer.nonvisit(ast)

    transformed_code = "\n\n".join(transformer.transformed_code)

    return transformer.transformed_funcs, transformed_code

def extract_includes(file_path):
    with open(file_path, 'r') as f:
        code = f.read()

    includes = re.findall(r'#\s*include\s*(<.*?>|".*?")', code)
    return includes

def main(input_file):
    if not os.path.isfile(input_file):
        print(f"'{input_file}' not found", file=sys.stderr)
        sys.exit(1)

    if not input_file.endswith('.c'):
        print("C file must end in '.c'", file=sys.stderr)
        sys.exit(1)

    transformed_funcs, transformed_code = transform_c_file(input_file)

    transformed_code = transformed_code.split('\n')
    transformed_code = ['    ' + line for line in transformed_code]
    transformed_code = '\n'.join(transformed_code)

    code_beginning = """
__attribute__ ((constructor)) intmax_t main2(int fun_args, ...);

int main() { // main() does nothing but return 0.
    return 0;
}

__attribute__ ((constructor)) intmax_t main2(int fun_args, ...) {
    if (fun_args < 100) { // If fun_args is less than 100, it means it's probably the "real" argc.
        return 0;
    }

    va_list args;
    va_start(args, fun_args);

"""
    code_ending = """
__attribute__ ((constructor)) void main3(int argc, char** argv) {
    main2(100, argc, argv);
}""" # XXX: We could probably turn main3 into a variadic function too and call main3 from main2 instead of main2 every time.

    print(code_beginning + transformed_code + "\nreturn 0;\n}\n" + code_ending)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: ./script.py file.c")
        sys.exit(1)

    input_file = sys.argv[1]
    try:
        main(input_file)
    except Exception as e:
        print(str(e))
    os.remove("yacctab.py")
    os.remove("lextab.py")
