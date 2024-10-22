#!/bin/sh

git status --ignored -s | grep '!!' | cut -c4-
