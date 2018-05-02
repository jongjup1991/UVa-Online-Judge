import random
import sys

numChimps = 20000
testCaseFile = open("problemid_10611_test_" + str(sys.argv[1]) + ".txt", "w")
testCaseFile.write(str(numChimps) + "\n")
chimpHeights = list()
for i in range(0, numChimps):
	chimpHeights.append(random.randint(1, 9999999))
chimpHeights.sort()
for i in chimpHeights:
	testCaseFile.write(str(i))
	testCaseFile.write(" ")
testCaseFile.write("\n")
numLuchuHeights = 20000
testCaseFile.write(str(numLuchuHeights) + "\n")
luchuHeights = list()
for i in range(0, numLuchuHeights):
	luchuHeights.append(random.randint(1, 9999999))
luchuHeights.sort()
for i in luchuHeights:
	testCaseFile.write(str(i))
	testCaseFile.write(" ")
testCaseFile.write("\n")
testCaseFile.close()