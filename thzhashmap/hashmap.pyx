# distutils: language = c++
# cython: language_level=3
"""
cdef extern from "<string>" namespace "std":
    cdef cppclass string:
        string() except +
        string(const char*) except +
        string(const string&) except +
        string& operator=(const string&) except +
        string& operator=(const char*) except +
        char& operator[](size_t) except +
        const char* c_str() const
"""
from .hashmap cimport HashMap
from libcpp.string cimport string
cdef class PyHashMap:
    cdef HashMap[string,string] *c_map
    
    def __cinit__(self):
        self.c_map = new HashMap[string,string]()
    
    def __dealloc__(self):
        del self.c_map
    
    def put(self, str key, str val):
        self.c_map.put(key.encode(), val.encode())
    
    def get(self, str key):
        return self.c_map.get(key.encode()).decode()
    
    def remove(self, str key):
        self.c_map.remove(key.encode())
    
    def print(self):
        self.c_map.print()
