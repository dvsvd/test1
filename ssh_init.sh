#!/bin/bash

eval `ssh-agent -s`
cd ~
ssh-add "ssh_laptop_github"