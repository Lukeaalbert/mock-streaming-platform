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

<b> content </b> <br />
content.h includes the Content class, as well as the Series and Movie child classes. content.cpp includes the implementation for these classes. <br />

<b> user </b> <br />
user.h includes the User class, and jsonparser.cpp includes the user class implementation. <br />

<b> strmsrv </b> <br />
strmsrv.h includes the Strmsrv class, which holds vectors of content and users as private data members. strmsrv.cpp includes the implementation for this classes. These implementation serve as the main logic for menu commands. <br />

<b> jsonparser </b> <br />
jsonparser.h includes the Jsonparser class, and jsonparser.cpp includes the unique json parser implementation for data input. <br />

<b> dataExp </b> <br />
dataExp.json is sample input. <br />

<b> mainStream </b> <br />
mainStream.cpp has the main() function and implement the main logic of running this program. <br />

For more information, please see the various files. Especially the header files. Information on specific methods and implementations can be found there. <b> Thanks! </b>
