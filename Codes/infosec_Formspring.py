__author__ = 'pushkar'
import hashlib
commompwd = open ('C:/Users/pushkar/Desktop/InfosecAssignment1Part2/banned.txt', 'r')
hashlist = open('C:/Users/pushkar/Desktop/InfosecAssignment1Part2/sha256list.txt', 'w')
formspringmatch = open('C:/Users/pushkar/Desktop/InfosecAssignment1Part2/formspringmatch.txt', 'w')
formspring = open('C:/Users/pushkar/Desktop/InfosecAssignment1Part2/formspring.txt', 'r')

list = commompwd.read().splitlines()

#creates SHA256 file for top 10k common (banned) passwords list with prepended 2 digit salt combinations
for val in list:
	for x in range(00, 100):
		y =  "%02d" % x
		newval = y + val
		hash = hashlib.sha256(newval).hexdigest()
		hashlist.write(newval)
		hashlist.write(':')
		hashlist.write(hash)
		hashlist.write('\n')
hashlist.close()

#match sha256 hashlist with formspring list to crack passwords and stores them in formspringmatch.txt 
hashfunc = open('C:/Users/pushkar/Desktop/InfosecAssignment1Part2/sha256list.txt', 'r')
comparisonlist = hashfunc.read().splitlines()
formspringlist = formspring.read().splitlines()
for value in comparisonlist:
	a = value.split(':')
	for eachval in formspringlist:
		if (eachval == a[1]):
			print eachval, '\t', a[0]
			formspringmatch.write(a[1])
			formspringmatch.write(':')
			formspringmatch.write(a[0])			
matched.close()
	
