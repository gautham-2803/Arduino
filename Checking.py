import requests
import json
# private_key = "KJaaMVZCG8TN3uFrgwO2"
# username = "marieyen23"
# device = 66952

link = "https://www.pushsafer.com/api-m?k=KJaaMVZCG8TN3uFrgwO2&d=66952"
f = requests.get(link)
f = f.json()
# print(f)
# print(f['messages'].keys()[0])
message_id = list(f['messages'].keys())[0]
x = f['messages'][message_id]['answer']
print(x)