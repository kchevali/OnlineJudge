#!/bin/bash

export test_dir=$(ls -td /Users/kevin/Downloads/*/ | head -1)
cp -a $test_dir $1