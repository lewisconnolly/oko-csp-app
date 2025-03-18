# oko-csp-app

Simple C++ program to connect to [OKO space](https://app.oko.live/) using [CSP API](https://connected-spaces-platform.net/api/library_root.html#full-api) and update a text component.

Run from command line, passing relevant parameters:

"oko_email" // argv[1]  
"plaintext_password" // argv[2]  
"Space Name" // argv[3]  
"Component Name" // argv[4]  
"Entity Name" // argv[5]  
"Text to Set" // argv[6]  

Example:

. .\oko-csp-app.exe "myokoemail@gmail.com" "mypassword" "Live D&D Arena" "Text Box" "Big Screen" "Hello, World!"
