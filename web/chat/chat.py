#coding:utf-8
import sys
import openai 
import codecs
#import urllib.parse
sys.stdout = codecs.getwriter('utf-8')(sys.stdout.detach()) 
data = sys.argv[1]
#urllib.parse.unquote()
# Set your API key
openai.api_key = "**********************************"

prompt =data

completion = openai.Completion.create(
    engine="text-davinci-003",
    prompt=prompt,
    max_tokens=1024,
    stop=None,
    temperature=0.5
)
# Print the generated text
print(completion.choices[0].text)
#with open('/home/lighthouse/chat.txt', 'w') as f:     
#        f.write(response)