#! /bin/bash

chmod -R 775 /Applications/PREDA/emscripten /Applications/PREDA/examples
osascript -e 'tell application (path to frontmost application as text)
display alert "make sure VS code `code` is installed in PATH(https://code.visualstudio.com/docs/setup/mac#_launching-from-the-command-line) and run `bash /Applications/PREDA/scripts/register_mac.sh`."
end'
exit 0
