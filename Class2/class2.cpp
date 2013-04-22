// Class2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <osg/Node>
#include <osg/Geode>
#include <osg/Geometry>
#include <osgViewer/Viewer>

osg::ref_ptr<osg::Node> createSceneGraph();

int _tmain(int argc, _TCHAR* argv[])
{

	// Set up and enter a simulation loop.
	osgViewer::Viewer viewer;
 	
	// The node is created using createSceneGraph()
	viewer.setSceneData( createSceneGraph() );
 	return viewer.run();

}


osg::ref_ptr<osg::Node> 
createSceneGraph()
{
	// Create an object to store geometry in.
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

	// Create an array of four vertices.
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	geom->setVertexArray( v.get() );
	v->push_back( osg::Vec3( -1.f, 0.f, -1.f ) );
	v->push_back( osg::Vec3( 1.f, 0.f, -1.f ) );
	v->push_back( osg::Vec3( 1.f, 0.f, 1.f ) );
	v->push_back( osg::Vec3( -1.f, 0.f, 1.f ) );

	// Create an array of four colors.
	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
	geom->setColorArray( c.get() );
	geom->setColorBinding( osg::Geometry::BIND_PER_VERTEX );
	c->push_back( osg::Vec4( 1.f, 0.f, 0.f, 1.f ) );
	c->push_back( osg::Vec4( 0.f, 1.f, 0.f, 1.f ) );
	c->push_back( osg::Vec4( 0.f, 0.f, 1.f, 1.f ) );
	c->push_back( osg::Vec4( 1.f, 1.f, 1.f, 1.f ) );

	// Create an array for the single normal.
	osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array;
	geom->setNormalArray( n.get() );
	geom->setNormalBinding( osg::Geometry::BIND_OVERALL );
	n->push_back( osg::Vec3( 0.f, -1.f, 0.f ) );
	
	// Draw a four-vertex quad from the stored data.
	geom->addPrimitiveSet(
	new osg::DrawArrays( osg::PrimitiveSet::QUADS, 0, 4 ) );

	// Add the Geometry (Drawable) to a Geode and
	// return the Geode.
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable( geom.get() );
	return geode.get();
}