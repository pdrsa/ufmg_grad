from sqlalchemy.orm import Session
from models import Usuario, UsuarioGrupo, Grupo, Evento, Post

class UsuarioRepository:
    @staticmethod
    def save(db: Session, user: Usuario):
    # If id is passed it updates else it creates
        if user.user_id:
            db.merge(user)
        else:
            db.add(user)
        db.commit()

    @staticmethod
    def find_by_id(db: Session, id: int) -> Usuario:
        return db.query(Usuario).filter(Usuario.user_id == id).first()
    
    @staticmethod
    def find_by_group_id(db: Session, id: int):
        return db.query(Usuario).join(UsuarioGrupo).filter(UsuarioGrupo.group_id == id)

    @staticmethod
    def login(db: Session, username: str, password: str):
        user = db.query(Usuario).filter(Usuario.username == username).first()

        return user.password == password

class GrupoRepository:
    @staticmethod
    def save(db: Session, group: Grupo):
    # If id is passed it updates else it creates
        if group.group_id:
            db.merge(group)
        else:
            db.add(group)
        db.commit()

    @staticmethod
    def find_by_id(db: Session, id: int) -> Grupo:
        return db.query(Grupo).filter(Grupo.grupo_id == id).first()
    
    @staticmethod
    def find_by_interest(db: Session, interest: str):
        return db.query(Grupo).filter(Grupo.interest == interest)

class EventoRepository:
    @staticmethod
    def save(db: Session, event: Evento):
    # If id is passed it updates else it creates
        if event.event_id:
            db.merge(event)
        else:
            db.add(event)
        db.commit()

    @staticmethod
    def find_by_group(db: Session, group_id: int):
        return db.query(Evento).filter(Evento.group_id == group_id)

class PostRepository:
    @staticmethod
    def save(db: Session, post: Post):
    # If id is passed it updates else it creates
        if post.post_id:
            db.merge(post)
        else:
            db.add(post)
        db.commit()

    @staticmethod
    def find_by_group_id(db: Session, group_id: int):
        return db.query(Post).filter(Post.group_id == group_id).order_by(Post.date)

class UsuarioGrupoRepository:
    @staticmethod
    def save(db: Session, user_group: UsuarioGrupo):
        db.add(UsuarioGrupo)
        db.commit()