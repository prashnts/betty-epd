#!/usr/bin/env python
# -*- coding: utf-8 -*-
import os
import re
import sys

from os import path
from codecs import open
from setuptools import setup

here = path.abspath(path.dirname(__file__))

setup(
  name='betty-epd',
  version='0.0.1',
  description="""""",
  author='Prashant Sinha',
  author_email='prashant+git@noop.pw',
  url='https://github.com/prashnts/betty-epd',
  download_url='https://github.com/prashnts/betty-epd/tarball/',
  packages=[
    'tools',
  ],
  include_package_data=True,
  license="MIT",
  zip_safe=False,
  classifiers=[
    'Development Status :: 3 - Alpha',
    'Intended Audience :: Developers',
    'License :: OSI Approved :: MIT License',
    'Natural Language :: English',
    'Programming Language :: Python :: 2',
    'Programming Language :: Python :: 2.7',
    'Programming Language :: Python :: 3',
    'Programming Language :: Python :: 3.2',
    'Programming Language :: Python :: 3.3',
    'Programming Language :: Python :: 3.4',
    'Programming Language :: Python :: 3.5',
  ],
)
