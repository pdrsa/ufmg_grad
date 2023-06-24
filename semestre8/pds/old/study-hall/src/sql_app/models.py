from operator import index
from sqlalchemy.schema import Column
from sqlalchemy.types import String, Integer, DateTime
from sqlalchemy import ForeignKey
from database import Base

class Usuario(Base):
    __tablename__ = 'tbl_Usuario'
    user_id = Column(Integer, primary_key = True, index = True)
    username = Column(String(50))
    fullname = Column(String(50))
    interests = Column(String(200))
    birthday = Column(String(50))
    password = Column(String(50))
    about = Column(String(200))
    registration_date = Column(DateTime)

class Grupo(Base):
    __tablename__  = 'tbl_Grupo'
    group_id = Column(Integer, primary_key = True, index = True)
    group_name = Column(String(50))
    organizer_name = Column(String(50))
    organizer_contact = Column(String(50))
    interest = Column(String(50))
    about = Column(String(200))
    group_create_date = Column(DateTime)

class Evento(Base):
    __tablename__ = 'tbl_Evento'
    event_id = Column(Integer, primary_key = True, index = True)
    group_id = Column(Integer)
    content = Column(String(200))
    date = Column(String(50))
    group_id = Column(Integer, ForeignKey("tbl_Grupo.group_id"))

class Post(Base):
    __tablename__ = 'tbl_Post'
    post_id = Column(Integer, primary_key = True, index = True)
    content = Column(String(200))
    date = Column(DateTime)
    group_id = Column(Integer, ForeignKey("tbl_Grupo.group_id"))

class UsuarioGrupo(Base):
    __tablename__ = 'tbl_Usuario_Grupo'
    user_group_id = Column(Integer, primary_key = True, index = True)
    user_id = Column(Integer, ForeignKey("tbl_Usuario.user_id"))
    group_id = Column(Integer, ForeignKey("tbl_Grupo.group_id"))