#! /usr/bin/env python3
import subprocess as sp
os_name = __import__('platform').system()
cmd,prefix = [],""
if os_name == 'Windows':
  cmd=["cmd", "/C"]
else:
  cmd = ["bash", "-c"]
  prefix = "./"
def GetTestData(exe):
  myout=sp.check_output(cmd+["%s%s"%(prefix, exe)])
  return myout.decode("utf8")
def Judge(a,b,testdata):
  f = open("test.in", "w+")
  f.write(testdata)
  f.close()
  c=sp.check_output(cmd+["%s%s<test.in"%(prefix, a)])
  d=sp.check_output(cmd+["%s%s<test.in"%(prefix, b)])
  if not c == d:
    print("answer: %s"%c.decode("utf8"),end="")
    print("output: %s"%d.decode("utf8"),end="")
    print("WA!")
    return False
  return True
if __name__ == '__main__':
  cnt = 0
  isOK = True
  while isOK:
    cnt += 1
    print(cnt)
    isOK=Judge("sol", "mysol", GetTestData("gen"))
