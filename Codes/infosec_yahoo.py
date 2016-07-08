__author__ = 'pushkar'
v = open('C:\Users\pushkar\Desktop\InfosecAssignment1Part2\Yahoo_out.txt', 'w')
f = open('C:\Users\pushkar\Desktop\InfosecAssignment1Part2\Yahoo.txt', 'r')
list = f.read().splitlines()
v.write('user_ID\t\t\t\tPasswords\n')
for value in list:
	a = value.split(':')
	v.write(a[1])
	v.write("\t\t\t")
	v.write(a[2])
	v.write("\n")
v.close()