# Assignment

Imagine a hollow sphere at the center of the coordinate frame (0,0,0).
The walls of the sphere are rigid.
The insides of the sphere contains a few 3D objects (refer list attached) that are made of trianlgles, which are constantly trying to escape from the clutches of the sphere, but bouces back again and again (randomly). These objects are rotating(randomly) and moving(randomly) within the boundry of the sphere. You are to visulize this scenario with following conditions:
- The camera is situated on the circumference of the sphere and always pointing at the center of the sphere (Hint: Use gluLookAt and Spherical Coordinate System). The camera's position on the circumference of the sphere should be controled using mouse movements
- Each triangle that consitutes the objects within the the sphere should be colored differently (hint: randomly color, use glcolor3f)
- The objects with in the sphere should be selectable using a left mouse click. Up on selection, the objects should stop its random movement and now move according to the users command. (Hint: Use stencil buffer for selecting a object)
- Upon selection (point 3), the user should be able to apply transformation (rotation, scaling and translation) depending on the mouse movement or keyboard strokes.
- These user transformations are also confined within the boundaries of the sphere.
- Upon deslection of the object, the object will resume its random movement with the sphere.
- Each student will have build 3 different 3d objects. 

Tarun: 35 PES1UG19CS535 Icosahedron Cuboid Cylinder

Ensure that the scene is properly lit (Hint: Use glMaterial, glLight)

NOTE:

The last date of submission is 20th Oct 2021. 11:59 PM IST
Late submission will be eligible for penality (4 marks everyday)
Any confusions please put a comment against this post, you will be answered.


> Marks division:40 marks for completion  10 marks for imagination (bring in your own features to the said assignments) 50 marks Total
