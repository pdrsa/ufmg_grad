from fastapi import FastAPI, Depends, status, Response
from fastapi.exceptions import HTTPException
from sqlalchemy.orm import Session
from database import SessionLocal, engine
from repositories import UsuarioRepository, GrupoRepository, EventoRepository, PostRepository, UsuarioGrupoRepository
from models import Usuario, UsuarioGrupo, Grupo, Evento, Post
import models
import schemas

app  = FastAPI()

def get_db():
    try:
        db = SessionLocal()
        yield db
    finally:
        db.close()

@app.get('/')
def read_root():
    return {"message": "Welcome to FastAPI"}

# Usuário ------------------------------------------------------------------------------

@app.post('/createUser', status_code=status.HTTP_201_CREATED)
async def createUser(request: schemas.UsuarioRequest, db: Session = Depends(get_db)):
    UsuarioRepository.save(db, Usuario(**request.dict()))

@app.post('/getUser', response_model=schemas.UsuarioResponse)
async def getUser(user_id: int, db: Session = Depends(get_db)):
    user = UsuarioRepository.find_by_id(db, user_id)
    if not user:
        raise HTTPException(
            status_code=status.HTTP_404_NOT_FOUND, detail = "Usuário não encontrado."
        )
    return schemas.UsuarioResponse.from_orm(user)

@app.post('/getUserGroups', response_model=list[schemas.UsuarioResponse])
async def getUserGroups(group_id: int, db: Session = Depends(get_db)):
    users = UsuarioRepository.find_by_group_id(db, group_id)
    return [schemas.UsuarioResponse.from_orm(user) for user in users]

# Grupos -----------------------------------------------------------------------------------

@app.post('/createGroup', status_code=status.HTTP_201_CREATED)
async def createGroup(request: schemas.GrupoRequest, db: Session = Depends(get_db)):
    GrupoRepository.save(db, Grupo(**request.dict()))

@app.post('/getGroup', response_model=schemas.GrupoResponse)
async def getGroup(id: int, db: Session = Depends(get_db)):
    group = GrupoRepository.find_by_id(db, id)
    return schemas.GrupoResponse.from_orm(group)

@app.post('/getGroupInterest', response_model=list[schemas.GrupoResponse])
async def getGroupInterest(interest: str, db: Session = Depends(get_db)):
    groups = GrupoRepository.find_by_interest(db, interest)
    return [schemas.GrupoResponse.from_orm(group) for group in groups]

# Eventos ----------------------------------------------------------------------------------------
@app.post('/createEvent', status_code=status.HTTP_201_CREATED)
async def createEvent(request: schemas.EventoRequest, db: Session = Depends(get_db)):
    EventoRepository.save(db, Evento(**request.dict()))

@app.post('/getEventGroup', response_model=list[schemas.EventoResponse])
async def getGroup(group_id: int, db: Session = Depends(get_db)):
    events = EventoRepository.find_by_group(db, group_id)
    return [schemas.EventoResponse.from_orm(event) for event in events]

# Posts --------------------------------------------------------------------------------------------
@app.post('/createPost', status_code=status.HTTP_201_CREATED)
async def createPost(request: schemas.PostRequest, db: Session = Depends(get_db)):
    PostRepository.save(db, Post(**request.dict()))

@app.post('/getPosts', response_model=list[schemas.PostResponse])
async def getPosts(group_id: int, db: Session = Depends(get_db)):
    posts = PostRepository.find_by_group_id(db, group_id)
    return [schemas.PostResponse.from_orm(post) for post in posts]

# Extra --------------------------------------------------------------------------------------------
@app.post('/login')
async def login(request: schemas.Login, db: Session = Depends(get_db)):
    if UsuarioRepository.login(db, request.username, request.password):
        return status.HTTP_200_OK
    else:
        return status.HTTP_401_UNAUTHORIZED

@app.post('/addUserGroup', status_code=status.HTTP_201_CREATED)
async def createPost(request: schemas.UserGroupRequest, db: Session = Depends(get_db)):
    UsuarioGrupoRepository.save(db, UsuarioGrupo(**request.dict()))
