from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

extensions = [
    Extension(
        "hashmap",
        sources=["hashmap.pyx", "hashmap_c.cpp"],
        language="c++",
        extra_compile_args=["-fmax-include-depth=300"] ,
    )
]

setup(
    name="HashMap",
    ext_modules=cythonize(extensions),
)
