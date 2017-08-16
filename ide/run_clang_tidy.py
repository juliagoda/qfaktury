#!/usr/bin/python3

import argparse
import os
import subprocess


def get_program_options():
    parser = argparse.ArgumentParser(description='Process some integers.')
    parser.add_argument('--build_dir')
    parser.add_argument('files', nargs='+')

    args = parser.parse_args()

    if not os.path.isdir(os.path.join(args.build_dir, ".ui")):
        print("Build dir does not contain '.ui' directory")
        exit()

    for file in args.files:
        if not os.path.isfile(file):
            print("'%s' is not valid file" % file)

    return args


def tidy_source(args):
    includes = (
        "/usr/include/qt",
        "/usr/include/qt/QtCore",
        "/usr/include/qt/QtGui",
        "/usr/include/qt/QtNetwork",
        "/usr/include/qt/QtPrintSupport",
        "/usr/include/qt/QtWidgets",
        "/usr/include/qt/QtXml",
        os.path.join(args.build_dir, ".ui"),
    )

    call_args = [
        "clang-tidy",
        "-header-filter=.*",
        "-fix",
        #"-config=%s" % os.path.join(os.path.dirname(os.path.realpath(__file__)), ".clang-tidy"),
        #"-dump-config",
    ]
    call_args.extend(args.files)
    call_args.extend([
        "--",
        "-std=c++11",
    ])

    for include in includes:
        call_args.append("-I" + include)

    print(call_args)

    subprocess.call(call_args)


def format_source(args):
    call_args = [
        "clang-format",
        "-i",
        #"-dump-config",
    ]
    call_args.extend(args.files)

    print(call_args)

    subprocess.call(call_args)


args = get_program_options()

tidy_source(args)
format_source(args)
