from sqlalchemy import create_engine
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker

DATABASE_URL = 'mysql+mysqlconnector://root:mynewpassword@localhost:3306/Study_Hall'

engine = create_engine(DATABASE_URL)
engine.table_names()
SessionLocal = sessionmaker(autocommit = False, autoflush = False, bind = engine)
Base = declarative_base()
Base.metadata.create_all(bind = engine)