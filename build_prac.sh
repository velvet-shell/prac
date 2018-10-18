#!/bin/bash

gcc $1 -O2 -std=gnu11 -Wall -Werror -Wno-pointer-sign -Wformat -Wformat-overflow -Wformat-security -Wnull-dereference -Wignored-qualifiers -Wshift-negative-value -Wswitch-default -Wduplicated-branches -Wduplicated-branches -Wfloat-equal -Wshadow -Wpointer-arith -Wpointer-compare -Wtype-limits -Wwrite-strings -Wdangling-else -Wempty-body -Wlogical-op -Wstrict-prototypes -Wold-style-declaration -Wold-style-definition -Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs -Wvla-larger-than=4096 -lm
