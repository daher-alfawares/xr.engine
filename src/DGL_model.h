/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.5 $
	$Date: 2004/09/11 05:18:51 $
	$Id: DGL_model.h,v 1.5 2004/09/11 05:18:51 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/



#ifndef ___DGL_MODEL_H
#define ___DGL_MODEL_H

/*
TODO List:
- Frustum Culling
*/

namespace DGL {
	class Frustum;
	class Font;

	class Model
		{

		public: virtual bool LoadModelData( std::string filename ) = 0;
				void         InitShaders( std::string filename ); // public, yet called internally
				void         Destroy();


		public: static void  _FrustumUpdate();

		public: void         Update(float msec);
				void         Render() const;
				void         RenderModelCoords() const;
				void         RenderModelName(DGL::Font &font) const;
				
				__inline void   Model::SetPosition(const Vector& v)	{this->position = v; this->calculateRadius();}
				__inline void   Model::SetAngles(const Vector& v){this->angles = v;}
				__inline Vector Model::GetPosition() const { return this->position; }
				__inline Vector	Model::GetAngles() const { return this->angles; }
				__inline float	Model::GetRadius() const { return this->radius; }

				Model();
				virtual	~Model();

		private:
			void Model::renderMeshMT( int _meshID) const;
			void Model::renderMesh( int _meshID) const;
	
		protected:
			//	Mesh
			struct Mesh
			{
				int materialIndex;
				int numTriangles;
				int *triangleIndices;
			};

			//	Material properties
			struct Material
			{
				Color				ambient,
										diffuse,
										specular,
										emissive;
				float				shininess;
				
				char				*textureFilename;
				const DGL::Shader	*shader;
			};

			//	Triangle structure
			struct Triangle
			{
				Vector	vertexNormals[3];
				float	texCoordS[3];
				float	texCoordT[3];
				int		vertexIndices[3];
			};

			//	Vertex structure
			struct Vertex
			{
				char	boneID;	// for skeletal animation
				Vector	location;
			};

		protected:

			bool		loaded;	// loaded?

			// Shader Library
			ShaderLib	shaderLib;

			//	Meshes used
			int			numMeshes;
			Mesh		*meshes;

			//	Materials used
			int			numMaterials;
			Material	*materials;

			//	Triangles used
			int			numTriangles;
			Triangle	*triangles;

			//	Vertices Used
			int			numVertices;
			Vertex		*vertices;

			// radius/position/angles
			float		radius;
			Vector		position;
			Vector		angles;

			// Name
			std::string	modelname;

			/////////////////////////////////////////////////
			// Frustum Culling: Using Spherical Method (fast)
			void calculateRadius();
			bool isInFrustum() const;

			static Frustum _frustum;
	};

}//namespace DGL

#endif // ___DGL_MODEL_H
