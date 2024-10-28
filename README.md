# echo-server

Using TCP, create a server that echoes all messages it receives, line by line.

If you send "abcd"(newline), you should get back "abcd"(newline). Then type another line, the same thing. As long as the connection stays alive. 

Implement a "-p" argument that specifies the port it listens to.

It only needs to accept one connection at a time, but it must accept new connections after one is terminated.

Test this with telnet; you'll probably need to install it.

Highly recommended: test it with your web browser, too.

EC: 25 more points for making it multi-threaded. (really easy)


## Steps

● One

    ○ Don’t die after one line!
● Two

    ○ Read all the lines until a CRLF (ignore the headers)
        ○ Parse the first line
● Three:

    ○ Then send back a valid response (no headers)
● Four:

    ○ If the path is /random, send back a random number (with headers)

    ○ text/html (wrap html: ec)

    ○  content-type: text/html
● Five:

    ○ If the path is /static/filename, return the contents of the file
    (open, read them, and send them)


## Client Agreement

● RFC 2616 - Hypertext Transfer Protocol -- HTTP/1.1

● Client message starts with a VERB line

    ○ VERB : GET, PUT, POST, DEL, HEAD, OPTIONS, PATCH

    ○ PATH : a path to a resource on the server

        ■ Starts with “/”

        ● Can be a full URL, but that’s not usual

        ■ NO SPACES ALLOWED

        ■ PROTOCOL: HTTP/1, HTTP/1.1, HTTP/1.2...

        ■ Ends with a CRLF
        
● Then headers, then a CRLF, then body