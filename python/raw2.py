#!/usr/bin/env python
def lop():
    st = raw_input('input something\n')
    while st.isdigit():
        print int(st)
        st = raw_input('input something\n')
lop()
