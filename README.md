# streaming-project
My streaming project is a mock streaming platform written in C++ that demonstrates my knowledge of OOP, 
inheritance, I/O streams/gathering data from input files, working across many files, and much more.
The service has <b> content (movies and series) </b> that can be watched by <b> users </b>.

In short, the user inputs a file with streaming data, and a Json parser (found in jsonparser.h and jsonparser.cpp) parses the data
and creates content and user objects for the streaming platform. The user navigates the platform with the menu (shown below)


QUIT:              0 <br />
LOGIN:             1 uname <br />
LOGOUT:            2 <br />
GET USER HISTORY:  3 <br />
SEARCH:            4 <* | string> <br />
WATCH:             5 <content-id> <br />
REVIEW:            6 <content-id> <number-of-stars> <br />
SUGGEST SIMILAR:   7 <content-id> <br />
