__author__ = 'pushkar'
import hashlib
commompwd = open ('C:/Users/pushkar/Desktop/InfosecAssignment1Part2/banned.txt', 'r')
decryptedlist = open('C:/Users/pushkar/Desktop/InfosecAssignment1Part2/decrypted.txt', 'w')
linkedin = open('C:/Users/pushkar/Desktop/InfosecAssignment1Part2/Linkedin.txt', 'r')
matched = open('C:/Users/pushkar/Desktop/InfosecAssignment1Part2/Linkedin_out.txt', 'w')

#creates SHA1 file for top 10k common (banned) passwords list
list = commompwd.read().splitlines()
for val in list:
		hash = hashlib.sha1(val).hexdigest()
		decryptedlist.write(val)
		decryptedlist.write("\t")
		decryptedlist.write(hash)
		decryptedlist.write("\n")
decryptedlist.close()

# creates a list with undecrypted passwords remaining
linkedinlist = linkedin.read().splitlines()
filtered = [val for val in linkedinlist if not val.startswith('00000')]
print filtered[0:10] 


#Comparison of common SHA1 hashes created from banned passwords list and filtered linkedIn list
hashfunc = open('C:/Users/pushkar/Desktop/InfosecAssignment1Part2/decrypted.txt', 'r')
comparisonlist = hashfunc.read().splitlines()

for value in comparisonlist:
	a = value.split('\t')
	for eachval in filtered:
		if (eachval == a[1]):
			print eachval, ':', a[0]
			matched.write(a[1])
			matched.write(':')
			matched.write(a[0])
			
matched.close()

		
