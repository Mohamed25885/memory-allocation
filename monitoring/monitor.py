import subprocess

brief = subprocess.check_output(
    ['wmic', 'process', 'list', "brief"])

parentprocessid = subprocess.check_output(
    ['wmic', 'process', 'get', "parentprocessid"])

virtualsize = subprocess.check_output(
    ['wmic', 'process', 'get', "virtualsize"])

brief = str(brief)
virtualsize = str(virtualsize)
parentprocessid = str(parentprocessid)

try:
    for i in range(len(brief)):
        entry = brief.split("\\r\\r\\n")[i]  
        entry = entry.split(" ")
        entry.pop(0)
        entry.append(virtualsize.split("\\r\\r\\n")[i])
        entry.append(parentprocessid.split("\\r\\r\\n")[i])
        entry = " ".join(entry)
        print(entry)
except IndexError as e:
    print("...END...")
