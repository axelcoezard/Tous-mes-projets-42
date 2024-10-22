#!/bin/sh

ls -l | sed '1n;N;s/.*\n//' 
