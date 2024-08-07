﻿from setuptools import setup
from setuptools.extension import Extension
from Cython.Build import cythonize
with open("./README.md",mode='r',encoding='utf-8') as f:
    des = f.read()
extensions = [
    Extension(
        "thzhashmap.hashmap",
        sources=["thzhashmap/hashmap.pyx", "thzhashmap/hashmap_c.cpp"],
        language="c++",
            )
]

setup(
    name="ThzHashMap",
    ext_modules=cythonize(extensions),
    version="1.0.6",               # 版本号
    author="Sen",
    package=['thzhashmap'],
    package_data={"thzhashmap": ["thzhashmap/*.pyx"]},
    install_requires=['Cython'],
    description="由天狐宗开发的哈希表，仅供学习",
    long_description=des,
    long_description_content_type='text/markdown',
    author_email="tianhuzong@qq.com",
    url="https://github.com/tianhuzong/hashmap",
    license="MIT",
    classifiers=[
        "Development Status :: 5 - Production/Stable",
        "License :: OSI Approved :: MIT License",
        "Programming Language :: Cython",
        "Programming Language :: C++",
        "Programming Language :: Python :: 3",
    ]
)
