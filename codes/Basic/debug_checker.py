#! /usr/bin/env python3
import subprocess, platform

os_name = platform.system()
cmd = []
prefix = ""

if os_name == 'Windows':
   cmd = ["cmd", "/C"]
else:
   cmd = ["bash", "-c"]
   prefix = "./"

def GetTestData(exe):
   myout = subprocess.check_output(cmd + ["%s%s"%(prefix, exe)])
   return myout.decode("utf8")
def Judge(a,b,testdata):
   f = open("test.in", "w+")
   f.write(testdata)
   f.close()
   myout = subprocess.check_output(cmd + ["%s%s < test.in"%(prefix, a)])
   ansout = subprocess.check_output(cmd + ["%s%s < test.in"%(prefix, b)])
   if not myout == ansout:
      print("answer: %s"%ansout.decode("utf8"),end="")
      print("output: %s"%myout.decode("utf8"),end="")
      print("WA!")
      return False
   return True
if __name__ == '__main__':
   cnt = 0
   isOK = True
   while isOK:
      cnt += 1
      print(cnt)
      isOK = Judge("1397.exe", "test.exe", GetTestData("gen.exe"))
