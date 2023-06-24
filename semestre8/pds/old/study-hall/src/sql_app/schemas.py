from datetime import date, datetime
from pydantic import BaseModel

class UsuarioBase(BaseModel):
    username  : str
    password  : str
    fullname  : str
    interests : str
    birthday  : str
    about     : str

class UsuarioRequest(UsuarioBase):
    ...

class UsuarioResponse(UsuarioBase):
    user_id: int
    class Config:
        orm_mode = True

class GrupoBase(BaseModel):
    group_name : str
    organizer_name : str
    organizer_contact : str
    interest : str
    about : str

class GrupoRequest(GrupoBase):
    ...

class GrupoResponse(GrupoBase):
    group_id: str
    class Config:
        orm_mode = True

class EventoBase(BaseModel):
    group_id : int
    event_name : str
    content : str
    date : str

class EventoRequest(EventoBase):
    ...

class EventoResponse(EventoBase):
    event_id: int
    class Config:
        orm_mode = True

class PostBase(BaseModel):
    group_id : int
    user_id : int
    content : str

class PostRequest(PostBase):
    ...

class PostResponse(PostBase):
    class Config:
        orm_mode = True

class Login(BaseModel):
    username : str
    password : str

class UserGroupRequest(BaseModel):
    user_id  : int
    group_id : int