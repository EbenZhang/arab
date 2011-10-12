#! /usr/bin/env python

#coding=utf-8

from setuptools import setup, find_packages
#import glob
setup(

    name='arab',

    version='1.0',

    packages = find_packages(),

    install_requires = ['pyzmq',
           'protobuf',
    ],

    description='python client for protobuf RPC, based on zeromq and protobuf',

    author='zhangyingneng',

    author_email='zhangyingneng@gmail.com',

    url='',

   # py_modules=glob.glob('arab/*.py')
)
