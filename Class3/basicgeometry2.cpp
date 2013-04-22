// basicgeom.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/PositionAttitudeTransform>


int _tmain(int argc, _TCHAR* argv[])
{

	   osg::ref_ptr<osg::Group> root = new osg::Group();
 	   osg::Geode* pyramidGeode = new osg::Geode();
 	   osg::ref_ptr<osg::Geometry> pyramidGeometry = new osg::Geometry();
 	
 	   // Associate the pyramid geometry with the pyramid geode
 	   // Add the pyramid geode to the root node of the scene graph.
 	   pyramidGeode->addDrawable(pyramidGeometry.get());
 	   root->addChild(pyramidGeode);
 	
 	   // Declare an array of vertices.
 	   osg::ref_ptr<osg::Vec3Array> pyramidVertices = new osg::Vec3Array;
 	   pyramidVertices->push_back( osg::Vec3( 0, 0, 0) ); // front left
 	   pyramidVertices->push_back( osg::Vec3(10, 0, 0) ); // front right
 	   pyramidVertices->push_back( osg::Vec3(10,10, 0) ); // back right
 	   pyramidVertices->push_back( osg::Vec3( 0,10, 0) ); // back left
 	   pyramidVertices->push_back( osg::Vec3( 5, 5,10) ); // peak
 	
 	   // Associate this set of vertices with the geometry associated with the
 	   // geode we added to the scene.
 	   pyramidGeometry->setVertexArray( pyramidVertices.get() );
 	   
 	   // Create a primitive set and add it to the pyramid geometry.
 	   osg::ref_ptr<osg::DrawElementsUInt> pyramidBase = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
 	   pyramidBase->push_back(3);
 	   pyramidBase->push_back(2);
 	   pyramidBase->push_back(1);
 	   pyramidBase->push_back(0);
 	   pyramidGeometry->addPrimitiveSet(pyramidBase.get());
 	
 	   // Repeat the same for each of the four sides. Again, vertices are
 	   // specified in counter-clockwise order.
 	   osg::ref_ptr<osg::DrawElementsUInt> pyramidFaceOne = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
 	   pyramidFaceOne->push_back(0);
 	   pyramidFaceOne->push_back(1);
 	   pyramidFaceOne->push_back(4);
 	   pyramidGeometry->addPrimitiveSet(pyramidFaceOne.get());
 	
 	   osg::ref_ptr<osg::DrawElementsUInt> pyramidFaceTwo = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
 	   pyramidFaceTwo->push_back(1);
 	   pyramidFaceTwo->push_back(2);
 	   pyramidFaceTwo->push_back(4);
 	   pyramidGeometry->addPrimitiveSet(pyramidFaceTwo.get());
 	
 	   osg::ref_ptr<osg::DrawElementsUInt> pyramidFaceThree = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
 	   pyramidFaceThree->push_back(2);
 	   pyramidFaceThree->push_back(3);
 	   pyramidFaceThree->push_back(4);
 	   pyramidGeometry->addPrimitiveSet(pyramidFaceThree.get());
 	
 	   osg::ref_ptr<osg::DrawElementsUInt> pyramidFaceFour = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
 	   pyramidFaceFour->push_back(3);
 	   pyramidFaceFour->push_back(0);
 	   pyramidFaceFour->push_back(4);
 	   pyramidGeometry->addPrimitiveSet(pyramidFaceFour.get());
 	
 	   //Declare and load an array of Vec4 elements to store colors.
 	   osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
 	   colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f) ); //index 0 red
 	   colors->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f) ); //index 1 green
 	   colors->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f) ); //index 2 blue
 	   colors->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f) ); //index 3 white
 	
 	   // Declare the variable that will match vertex array elements to color
 	   // array elements. 
	   // Needed incase the number of vertices and the number of colors are different.
	   osg::ref_ptr<osg::TemplateIndexArray<unsigned int, osg::Array::UIntArrayType,4,4>> colorIndexArray;
 	   colorIndexArray = new osg::TemplateIndexArray<unsigned int, osg::Array::UIntArrayType,4,4>; 	  
 	   colorIndexArray->push_back(0); // vertex 0 assigned color array element 0
 	   colorIndexArray->push_back(1); // vertex 1 assigned color array element 1
 	   colorIndexArray->push_back(2); // vertex 2 assigned color array element 2
 	   colorIndexArray->push_back(3); // vertex 3 assigned color array element 3
 	   colorIndexArray->push_back(0); // vertex 4 assigned color array element 0
 	
 	   //The next step is to associate the array of colors with the geometry,
 	   //assign the color indices created above to the geometry and set the
 	   //binding mode to BIND_PER_VERTEX.
 	   pyramidGeometry->setColorArray(colors.get());
 	   pyramidGeometry->setColorIndices(colorIndexArray.get());
 	   pyramidGeometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
 	
 	   // Declare and initialize a transform node.
 	   osg::PositionAttitudeTransform* pyramidTwoXForm = new osg::PositionAttitudeTransform();
 	
 	   // Use the 'addChild' method of the osg::Group class to
 	   // add the transform as a child of the root node and the
 	   // pyramid node as a child of the transform.
 	   root->addChild(pyramidTwoXForm);
 	   pyramidTwoXForm->addChild(pyramidGeode);
 	
 	   // Declare and initialize a Vec3 instance to change the
 	   // position of the model in the scene
 	   osg::Vec3 pyramidTwoPosition(15,0,0);
 	   pyramidTwoXForm->setPosition( pyramidTwoPosition );
 	
 	   // The final step is to set up and enter a simulation loop.
 	   osgViewer::Viewer viewer;
 	
 	   viewer.setSceneData( root.get() );
 	   return viewer.run();
}

