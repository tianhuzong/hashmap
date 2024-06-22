from libcpp.string cimport string
cdef extern from "hashmap_c.cpp":
    cdef cppclass HashMap[K,V]:
        #HashMap()
        K& put(K& key, V& val)
        K& get(K& key)
        void remove(K& key)
        void print()

