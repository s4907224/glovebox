#include "geometry/VAO.h"

int gbox::VAO::m_instance_counter = 0;

gbox::VAO::VAO(std::string _file_path)
{
  m_ID = m_instance_counter++;

  load_from_obj(_file_path);
  create_VAO();

  #ifdef DEBUG_PRINTS
  std::cout<<"Ctor called for VAO with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
  #endif
}

gbox::VAO::~VAO()
{
  glDeleteVertexArrays(1, &m_VAO_id);
  glDeleteBuffers(1, &m_VBO_id);
  glDeleteBuffers(1, &m_EBO_id);

  #ifdef DEBUG_PRINTS  
  std::cout<<"Dtor called for VAO with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
  #endif
}

gbox::VAO::VAO(const VAO& _vao_other)
{
  m_ID = m_instance_counter++;

  m_VAO_id = _vao_other.m_VAO_id;
  m_VBO_id = _vao_other.m_VBO_id;

  #ifdef DEBUG_PRINTS
  std::cout<<"Copy ctor called for VAO with ID "<<m_ID<<" and VAO with ID "<<_vao_other.m_ID<<'\n';
  #endif
}

gbox::VAO& gbox::VAO::operator=(const VAO& _vao_other)
{
  m_ID = _vao_other.m_ID;

  m_VAO_id = _vao_other.m_VAO_id;
  m_VBO_id = _vao_other.m_VBO_id;

  #ifdef DEBUG_PRINTS
  std::cout<<"Copy assignment called for VAO with ID "<<m_ID<<" and VAO with ID "<<_vao_other.m_ID<<'\n';
  #endif
  
  return *this;
}

gbox::VAO::VAO(VAO&& _vao_other)
{
  m_ID = _vao_other.m_ID;

  m_VAO_id = _vao_other.m_VAO_id;
  m_VBO_id = _vao_other.m_VBO_id;

  #ifdef DEBUG_PRINTS
  std::cout<<"Move ctor called for VAO with ID "<<m_ID<<" and VAO with ID "<<_vao_other.m_ID<<'\n';
  #endif

  _vao_other.m_ID = -1;
}

gbox::VAO& gbox::VAO::operator=(VAO&& _vao_other)
{
  m_ID = _vao_other.m_ID;

  m_VAO_id = _vao_other.m_VAO_id;
  m_VBO_id = _vao_other.m_VBO_id;

  #ifdef DEBUG_PRINTS
  std::cout<<"Move assignment called for VAO with ID "<<m_ID<<" and VAO with ID "<<_vao_other.m_ID<<'\n';
  #endif

  _vao_other.m_ID = -1;
  return *this;
}

void gbox::VAO::create_VAO()
{
  glGenVertexArrays(1, &m_VAO_id);
  glGenBuffers(1, &m_VBO_id);
  glGenBuffers(1, &m_EBO_id);

  glBindVertexArray(m_VAO_id);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO_id);

  glBufferData(GL_ARRAY_BUFFER, m_vertex_data.size() * sizeof(glm::vec3), &m_vertex_data[0].x, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3) * 2, 0);
  glEnableVertexAttribArray(0);


  glBufferData(GL_ARRAY_BUFFER, m_vertex_data.size() * sizeof(glm::vec3), &m_vertex_data[0].x, GL_STATIC_DRAW);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(glm::vec3) * 2, (void*) (sizeof(glm::vec3)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_vertex_indices.size(), &m_vertex_indices[0], GL_STATIC_DRAW);

  glBindVertexArray(m_VAO_id);
}

void gbox::VAO::load_from_obj(std::string _obj_file)
{
  std::ifstream fs_obj;
  fs_obj.open(_obj_file);

  std::vector<glm::vec3> vp;
  std::vector<glm::vec3> vn;
  std::vector<int> idx;

  std::array<std::string, 3> prefixes = {
    "v ",
    "vn",
    "f "
  };

  if (fs_obj.is_open())
  {
    std::string line;
    while (std::getline (fs_obj, line))
    {
      std::string prefix = line.substr(0, 2);
      
      std::string s_data;

      bool p = std::find(std::begin(prefixes), std::end(prefixes), prefix) == std::end(prefixes);
      if (p)
      {
        continue;
      }

      if (prefix == "v ")
      {
        // std::cout<<line.substr(2)<<'\n';
        std::istringstream vertex_data(line.substr(2));
        double x,y,z;
        vertex_data>>x;vertex_data>>y;vertex_data>>z;
        glm::vec3 vert {x,y,z};
        vp.push_back(vert);
      }
      else if (prefix == "vn")
      {
        // std::cout<<line.substr(3)<<'\n';
        std::istringstream vertex_data(line.substr(2));
        double x,y,z;
        vertex_data>>x;vertex_data>>y;vertex_data>>z;
        glm::vec3 vert {x,y,z};

        vn.push_back(vert);
      }
      else if (prefix  == "f ")
      {
        int v_1, v_2, v_3;
        int n_1, n_2, n_3;
        int uv_1, uv_2, uv_3;

        const char* chh=line.c_str();
        sscanf (chh, "f %i/%i/%i %i/%i/%i %i/%i/%i", &v_1, &n_1, &uv_1, &v_2, &n_2, &uv_2, &v_3, &n_3, &uv_3);

        idx.push_back(--v_1);
        idx.push_back(--v_2);
        idx.push_back(--v_3);
      }
    }
    fs_obj.close();
  }

  m_vertex_data.clear();
  for (size_t i = 0; i < vp.size(); i++)
  {
    m_vertex_data.push_back(vp[i]);
    m_vertex_data.push_back(vn[i]);
  }

  m_vertex_indices.clear();
  for (size_t i = 0; i < idx.size(); i++)
  {
    m_vertex_indices.push_back(idx[i]);
  }
}

void gbox::VAO::draw()
{
  glBindVertexArray(m_VAO_id);

  for (auto shader_mesh_data : m_meshes)
  {
    shader_mesh_data.first->use();

    for (auto mesh : shader_mesh_data.second)
    {
      auto mvp = mesh->update_mvp();
      glUniformMatrix4fv(0, 1, false, glm::value_ptr(*mvp));
      glDrawElements(GL_TRIANGLES, m_vertex_indices.size(), GL_UNSIGNED_INT, 0);
    }
  }
}

void gbox::VAO::register_mesh(std::shared_ptr<gbox::Mesh> _mesh)
{
  auto shader_program = _mesh->get_shader_program();
  m_meshes[shader_program].push_back(_mesh);
}

bool gbox::VAO::unregister_mesh(std::shared_ptr<gbox::Mesh> _mesh)
{
  auto shader_program = _mesh->get_shader_program();
  auto iter = find(m_meshes[shader_program].begin(), m_meshes[shader_program].end(), _mesh);
  if (iter == m_meshes[shader_program].end())
  {
    return false;
  }

  m_meshes[shader_program].erase(iter);
  return true;
}