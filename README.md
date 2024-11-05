# echo-server

Using TCP, create a server that echoes all messages it receives, line by line.

If you send "abcd"(newline), you should get back "abcd"(newline). Then type another line, the same thing. As long as the connection stays alive. 

Implement a "-p" argument that specifies the port it listens to.

It only needs to accept one connection at a time, but it must accept new connections after one is terminated.

Test this with telnet; you'll probably need to install it.

Highly recommended: test it with your web browser, too.

EC: 25 more points for making it multi-threaded. (really easy)

(Surprise: this will be the basis of Asst 12, so ensure you understand it completely. And asst 12 *must* be multi-threaded)

## Steps

- one: 
    - Don't die after one line
- Two: 
    - read all the lines until a CRLF (ifnore the headers)
        - parse the first line.
- three: 
    - send back a valid response (no headers)
- four: 
    - if the path is /random, send back a random (with headers)
    - content-type: text/html
    - text/html
- five:
    - if the path is /static/filename, return the contents of the file
    (open, read them, and send them back)

    ?


## Client Agreement

- RFC 2616 - Hypertext Transfer Protocol -- HTTP/1.1

- Client message starts with a VERB line
    - VERB : GET, PUT, POST, DEL, HEAD, OPTIONS, PATCH

- PATH : a path to a resource on the server
        - Starts with “/”

        - Can be a full URL, but that's not usual

        - NO SPACES ALLOWED

        - PROTOCOL: HTTP/1, HTTP/1.1, HTTP/1.2...

        - Ends with a CRLF
       
Then headers, then a CRLF, then body


## more notes from class:
echo server (type abc it returns abc to you)
- web server coming up

socket/ bind / listen / accept

send them back with write()

- port - room location
listen back log = how many people can talk
in handle connection; read it from client and read it back

have to have two terminals; text from one and recieve it from the other terminal
connect using tenelect

only listened and honors ones

process duplicates everything 
