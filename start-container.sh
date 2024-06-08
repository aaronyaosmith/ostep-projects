#!/bin/bash

lima nerdctl run --rm -it \
  --mount "type=bind,source=$(git rev-parse --show-toplevel),target=/ostep-projects" \
  ostep-projects
