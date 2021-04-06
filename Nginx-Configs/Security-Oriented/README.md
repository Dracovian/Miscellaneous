# Security-Oriented Nginx Configuration

## Information
* [Host](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Host "Host info at MDN")
* [Origin](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Origin "Origin info at MDN")
* [X-Frame-Options](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/X-Frame-Options "X-Frame-Options info at MDN")
* [X-Content-Type-Options](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/X-Content-Type-Options "X-Content-Type-Options info at MDN")
* [X-XSS-Protection](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/X-XSS-Protection "X-XSS-Protection info at MDN")
* [Referrer-Policy](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Referrer-Policy "Referrer-Policy info at MDN")
* [Strict-Transport-Security](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Strict-Transport-Security "Strict-Transport-Security info at MDN")
* [Content-Security-Policy](https://developer.mozilla.org/en-US/docs/Web/HTTP/CSP "Content-Security-Policy info at MDN")

## Missing
* [Content-Type](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Content-Type "Content-Type info at MDN")

## Extra security information
1. **Prevent XSS attacks** by pushing all user-input information through a filtering scheme that removes HTML tags using:
	* PHP: [htmlspecialchars](https://secure.php.net/manual/en/function.htmlspecialchars.php "htmlspecialchars documentation")
	* JavaScript: [encodeURIComponent](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/encodeURIComponent "encodeURIComponent info at MDN")
	* Python 3: [urllib.parse.quote](https://docs.python.org/3/library/urllib.parse.html "urllib.parse documentation")
	* Python 2: [urllib.quote](https://docs.python.org/2/library/urllib.html "urllib documentation")
	* Other: Just use any built-in function that escapes characters (or make your own if you have to)
2. **Prevent CSRF attacks** by creating a session value (token) to check for when a visitor requests website content. If you use an external CDN then you'll have to make sure that you apply CSRF protection to the CDN or ensure that the CDN you're using already has some form of CSRF protection implemented.
3. **Prevent SQL injections** by preparing your statements.
	* PHP: [PDO->prepare](http://php.net/manual/en/pdo.prepare.php "PDO->prepare documentation")
	* JavaScript (Node.JS): [connection.query](https://github.com/mysqljs/mysql "mysqljs repository")
	* Python: [cursor.execute](https://dev.mysql.com/doc/connector-python/en/connector-python-api-mysqlcursor-execute.html "cursor.execute documentation")
4. **Prevent RCE attacks** by ensuring that no visitor can have their inputs evaluated as code:
	* PHP: [eval](http://php.net/manual/en/function.eval.php "eval documentation")
	* JavaScript: [eval](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/eval "eval info at MDN")
	* Python: [eval](https://docs.python.org/3/library/functions.html#eval "eval documentation")
5. [**Prevent XXE injections**](https://www.owasp.org/index.php/XML_External_Entity_(XXE)_Processing "XXE info at OWASP") by switching from XML to JSON.
6. **Prevent poor encryption** by [switching from ECB to CBC](https://datalocker.com/what-is-the-difference-between-ecb-mode-versus-cbc-mode-aes-encryption/ "ECB versus CBC at datalocker")
7. **Avoid MD5 and SHA1 for password hashing** by opting for bcrypt, scrypt, or Argon2 instead.
8. **Avoid vulnerability scanner software from wreaking havoc on your server** by implementing a Turing test of sorts upon initial site access *(store the success attempt in sessions and never in cookies)* such as ReCaptcha.
9. **Avoid exposure of user credentials from MITM attacks** by implementing SSL (HTTPS) on your website.
10. **Never trust user input**