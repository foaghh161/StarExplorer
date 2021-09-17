# StarExplorer
Given a database containing of all the exoplanets, this programs lets you navigate through the galaxies, solarsystems and stars! You can also search for a specific star or planet by just its nume or number. There is also a Admin gui, where the admin kan administrate the system by adding or deleteng exoplanets.

This project was achivied by a grupp of good student in "Programvaruutveckling" course 


Start page
The start page has four buttons:
The button “Search” opens the Search Page. 
The button “Explore” opens up the Galaxy View.
The button “Exit” closes down the program. (this can also be done with the X in top corner)
The button “Admin Mode” opens up a pop up window where login information can be filled out. If login is successful the Admin Page will open. 

![image](https://user-images.githubusercontent.com/32487903/133765485-cffd5bf8-029f-461f-871b-8a9d4379d8e9.png)


Galaxy view
This view represents all the stars in the database. The gray section on the right is an information panel which will show information about the star. The galaxy-view can be interacted with the help of the +/- buttons to zoom in and out. The arrow buttons will move the camera view around and the house button resets the view. The buttons are mapped to keyboard shortcuts. 
Arrow keys moves the camera-view around
‘+’ key zooms in 
‘-’ key zooms out 
Space key will reset view
Left mouse button will select the closest star to the mouse pointer and fill out the information panel

The two buttons on the bottom of the window screen will move to a different screen. 
The button “Back” opens up Start Page
The button “View System” opens the System View

![image](https://user-images.githubusercontent.com/32487903/133765574-4e3477be-520c-4456-bad6-c27537cdbace.png)


System view
This view represents the star and all planets of the solar system. The gray section on the right is an information panel which will show information about the star. 

The left mouse button will select the closest star or planet to the mouse pointer and fill out the information panel.

The buttons on the screen will open a different window.
The button “Home” opens up the Start Page
The button “Back” opens up Galaxy view
The button “Sky View” opens the Sky view

![image](https://user-images.githubusercontent.com/32487903/133765649-a101c3cf-479d-444e-bbf8-414ff3874920.png)


Sky view
This view represents the skyperspectiv of the current star. The gray section on the right is an information panel which will show information about the star. 

The galaxy-view can be interacted with the help of the arrow buttons to move around and the house button to reset the view.. The buttons are mapped to keyboard shortcuts. 
Arrow keys moves the camera-view around
Space key resets the view
Left mouse button will select the closest star to the mouse pointer and fill out the information panel

The two buttons on the bottom of the window screen will move to a different screen. 
The button “Home” opens up the Start Page
The button “Back” opens up System View
The button “View System” opens the System View

![image](https://user-images.githubusercontent.com/32487903/133765689-bb83dd76-2edc-4167-80bd-42573eae23c7.png)


Search page
This page can be used to search planets or stars. The search results will be shown in the white table. The left mouse button will select the current row. 

There are four search fields:
In the “Name” search field is where the name of planets or stars can be filled in. 
In the “X” search field is where the x-coordinate of the cartesian coordinates are filled in. This field can only be filled in while the star table is selected.  
In the “Y” search field is where the x-coordinate of the cartesian coordinates are filled in. This field can only be filled in while the star table is selected.  
In the “Z” search field is where the x-coordinate of the cartesian coordinates are filled in. This field can only be filled in while the star table is selected.  

There are three buttons:
The button “Search” fills out the information in the table.
The button “Home” opens up the Start Page
The button “View Star”/ “View Planet” opens up the System view of the selected row in the search result

![image](https://user-images.githubusercontent.com/32487903/133765743-c798f88a-0264-4343-9a01-33438189b75f.png)


Admin page
This is the administrator menu With this menu you have the ability to change data in the database. 
	
The three buttons on the admin page performs different actions:
The button “Add New” opens up the pop up menu. This menu decides whether to add a star or a planet
The add system opens up Admin form
The add Planet opens up Admin Search
The cancel closes the pop up
The button “Change Existing” opens up the pop up menu. This menu decides whether to change star or planet
The add system opens up Admin Search
The add Planet opens up Admin Search
The cancel closes the pop up
The button “Log out” logs admin session out and opens the Start Page 

![image](https://user-images.githubusercontent.com/32487903/133765787-7ead0909-3437-4335-bbc8-fdc10c9c1554.png)



Admin Search
The search field requires different input depending on which pop up menu was clicked:
Add planet requires the hipparcos id of the star it wants to be added to
Change Star requires the hipparcos id of the star that needs to be changed
Change Planet requires the planet name of the planet that needs to be changed

There are three buttons:
The button “Search” fills out the information in the table.
The button “Cancel” opens up the Admin page
The button “Confirm” opens up the Admin Form
If “Change Planet” pop up button is clicked a row need to be selected with mouse button left.


![image](https://user-images.githubusercontent.com/32487903/133765848-c56cc420-197e-46f4-944e-d96761dc077c.png)


Admin Form
On this window a form with all the information about the star or planet can be filled out or changed. Some fields requires to be filled out:
From Star
The X coordinate
Y Coordinate
Z Coordinate
Hipparcos Id
From Planet
Planet Name

Some fields require different data types. There are three different data types: whole number, decimal numbers and text. This means that letters are not accepted in whole number- or decimal number fields although numbers are allowed in text fields.

The two buttons perform different actions:
The button “Confirm” will perform the change/ add to the star/ planet and open up Admin Page
The button “Cancel will cancel the change/ add to the star/ planet and open up Admin Page


![image](https://user-images.githubusercontent.com/32487903/133765898-d8881087-708d-4b80-b167-66b01165128a.png)



