INTRODUCTION
-----------
Plugin Name: GetResponse Plugin
Description: This plug-in/module enables installation of a GetResponse 
fully customizable sign up form on your Drupal site. To find out more 
about GetResponse, please visit: http://www.getresponse.com/about-us
Version: 2.0.0
Author: Grzegorz Struczynski, Sylwester Okroj
License: GPL2


GETRESPONSE INTEGRATION
-----------
This plug-in/module enables installation of a GetResponse fully customizable 
sign up form on your Drupal site. Once a web form is created and added to 
the site the visitors are automatically added to your GetResponse contact
list and send a confirmation email. The plug-in additionally offers sign-up 
upon leaving a comment. 


INSTALLATION:
-----------

To use GetResponse web forms on a Drupal web page, 
follow these instructions:

In GetResponse, find the WID tag.
1. Log in to your GetResponse account. 

2. Create a new web form by clicking Web Forms -> Create new 
or choose an existing web form by clicking Web Forms -> Web 
Forms list. 

3. If you are designing a new form, advance to the “Publish” 
screen and scroll down to view the HTML code. If you are using 
an existing form, click Web Forms -> Web Forms list then click 
the “view source” link for the form you select. 

4. In the HTML code, find the URL of the Web Form and copy 
the WID number. It's the number that follows “WID=”.  

In Drupal, enter the GetResponse WID tag.
5. To change the layout of the web form on your Drupal page, 
log in to your Drupal admin account. Go to "Configuration", 
scroll down to the Web Services section and click 
"GetResponse". 

6. In the Web form ID field, enter the WID tag you found in 
your GetResponse web form editor page. 

7. In the “Style” pulldown menu, choose the GetResponse 
layout or the Drupal standard layout for web forms. 

8. Last but not least, decide where the GetResponse web form 
should appear on your website. Click "Structure -> Blocks", 
scroll down to the "Disabled" section and locate the pulldown 
menu beside the GetResponse WebForm plugin. Click to select 
the position where the web form should be shown. 

To enable blog readers to subscribe to your GetResponse 
campaigns via blog comments, follow these instructions:

In GetResponse, find the WID tag.
1. Log in to your GetResponse account. 
2. Create a new web form by clicking Web Forms -> Create new 
or choose an existing web form by clicking Web Forms -> Web 
Forms list. 

3. If you are designing a new form, advance to the “Publish”  
screen and scroll down to view the HTML code. If you are using 
an existing form, click Web Forms -> Web Forms list then click 
the “view source” link for the form you select. 

4. In the HTML code, find the URL of the Web Form and copy 
the WID number. It's the number that follows “WID=”.  

In Drupal, enter the GetResponse WID tag.
5. In the “Web form ID” field, enter the WID tag you found in 
your GetResponse web form editor page. 

5. Click "Configuration", scroll down to the Web Services 
section, and make sure "Comment integration" at “Subscribe 
via Comment” is switched ON. 

6. In the line below "Additional text," choose a call-to-action 
sentence. 

7. To activate the commenting function, click "Structure -> 
Content types". You can either create a new content type or 
click "edit" at an existing one. Find the appropriate options in 
the lower left corner of the "Comment settings" tab. It's 
important that the "Anonymous commenting" pulldown menu 
is activated on "Anonymous posters must leave their contact 
information". 
