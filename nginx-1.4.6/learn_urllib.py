#!/usr/bin/python
# coding=utf-8

import urllib
import urllib2
import sys

url = 'http://127.0.0.1:8714/redirected/'
if len(sys.argv) > 1:
    url = sys.argv[1]

debug=0
user_agent = "learn_urllib.py"
values1 = {'name' : '丁亦川',
        'location' : 'HangZhou'}

data = urllib.urlencode(values1)
if debug:
    print "data1:", data

values2 = [('name', 'jpp'),
        ('location', 'HangZhou')]
data = urllib.urlencode(values2)
if debug:
    print "data2:", data

values3 = {'name' : '丁亦川',
        'location' : 'HangZhou',
        'language' : ['Python', 'cpp', 'Java']}
data = urllib.urlencode(values3)
if debug:
    print "data3(doseq=False):", data
data = urllib.urlencode(values3, True)
if debug:
    print "data3(doseq=True):", data

headers = { 'User-Agent' : user_agent }
req = urllib2.Request(url, data, headers)
req = urllib2.Request(url, None, headers)
req.add_data("urllib add data into request")

try:
    response = urllib2.urlopen(req)

except urllib2.URLError,e:
    if hasattr(e, "reason"):
        print 'Error reason: ', e.reason
    if hasattr(e, "code"):
        print 'Error code: ', e.code
        sys.exit()
else:
    url=response.geturl()
    print "url:%s" % url

    the_page = response.read()
#    info=response.info()
#    code=response.getcode()
#    print "info:%s" % str(info)
#    print "code:%s" % str(code)
    print "the_page:\n%s" % str(the_page)
#print "url:%s info:%s" % "url" "code"
