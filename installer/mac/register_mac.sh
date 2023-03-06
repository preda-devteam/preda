#! /bin/bash -e

code --install-extension /Applications/PREDA/extensions/preda.vsix
python3 -c 'import os,json
home_dir=os.path.expanduser("~")
setting=os.path.join(home_dir, "Library", "Application Support", "Code", "User", "settings.json")
os.makedirs(os.path.dirname(setting), exist_ok=True)
if not os.path.exists(setting):
	open(setting,"w").close()
with open(setting,"r") as f:
	s=f.read()
if len(s) < 2:
	s="{}"
j=json.loads(s)
j["Preda.path"]="/Applications/PREDA/bin/chsimu"
with open(setting,"w") as f:
	json.dump(j,f,indent=2)
	f.close()'
osascript -e 'tell application (path to frontmost application as text)
display alert "PREDA Language Toolchain installed. Use VS Code to open\n/Applications/PREDA/examples folder to browse sample contracts and scripts"
end'

