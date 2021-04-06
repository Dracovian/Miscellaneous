# SimpleRequests
This is a simple requests module for Python 2 and Python 3.
I'll be making use of this in my future scripts since I've been meaning to streamline the whole process for a while.

## Usage:
```py
# Import SimpleRequest from SimpleRequests.
from SimpleRequests import SimpleRequest

# Call our SimpleRequest class (which is just an object).
simplerequest = SimpleRequest()

# Grab textual data with ease.
data = simplerequest.request.grab_page('https://test.domain/', True)
print(data)

# Or grab JSON data instead.
data = simplerequest.request.grab_page('https://test.domain/file.json')
print(data)
```

## Functions:
### set_header(name, value)
This can be used to create or alter a request header.

```py
# This will create our header.
simplerequest.request.set_header('host', 'fake.domain')

# This will overwrite our header.
simplerequest.request.set_header('host', 'test.domain')
```

### del_header(name)
This can be used to delete a request header.

```py
# This should print "True".
print('True' if simplerequest.request.headers['host'] else 'False')

# Now to delete our header.
simplerequest.request.del_header('host')

# This should print "False".
print('True' if simplerequest.request.headers['host'] else 'False')
```

### get_response(url)
This can be used to gather a simple response from a request.
If the returned value is "None" then something went wrong when gathering data.

```py
# Gather our response.
resp = simplerequest.request.get_response('https://test.domain/')

# Print our response.
print(resp)
```

This will be a urllib2 response for Python 2 and an http.client response for Python 3.

### stream_file(url, filepath, filename, buffer, usebuffer)
This can be used to download the contents of a binary in chunks.
The default chunk size is 512 bytes meaning that you'll be grabbing data in chunks of 512 bytes at a time.
Faster results can be had with a larger buffer, this is dependent on the connection speed between the client and the site.

The usebuffer boolean flag is defaulted to True meaning that we will be streaming the data, but setting it to False will simply
choose not to use the streaming function (fallback reasons).

```py
# Import os.path and os.getcwd for this example.
from os import getcwd, path

# Let's download our example JSON file in 512 byte chunks for reasons.
simplerequest.request.stream_file('https://test.domain/file.json', 'downloads', 'file.json')

# Let's open our file for reading.
with open(path.join(getcwd(), 'downloads', 'file.json'), 'r') as jsondata:
    print(jsondata.read())
```

### grab_page(url, binary)
This can be used to grab the contents of a page.
The default setting for binary is "False", meaning that grab_page will attempt to read JSON data by default.
This will definitely be subject to change in the future.

```py
# Let's use our example site again...
data = simplerequest.request.grab_page('https://test.domain/', True)

# Print out the textual contents of our example site.
print(data)
```
