CREATE EXTENSION IF NOT EXISTS "uuid-ossp";
CREATE EXTENSION IF NOT EXISTS "pgcrypto";

CREATE TABLE users (
    id                      varchar (36) PRIMARY KEY,
    username                varchar (256) NOT NULL,
    email                   varchar (256) NOT NULL,
    pswhash                 varchar (256) NOT NULL,

    CONSTRAINT              UK_USERS_USERNAME UNIQUE (username),
    CONSTRAINT              UK_USERS_EMAIL UNIQUE (email)
);

CREATE TABLE stories (
    id          varchar (36) PRIMARY KEY,
    userid      VARCHAR,
    content     VARCHAR
);

INSERT INTO users
(id, username, email, pswhash) VALUES ('4bb48865-1a84-49c7-94eb-148ed2f9d7a5', 'admin', 'admin@domain.com', crypt('admin', gen_salt('bf', 8)));

INSERT INTO stories
(id, userid, content) VALUES
('457d5263-8ca7-49dd-b8d2-1aa1c181cdb5', '4bb48865-1a84-49c7-94eb-148ed2f9d7a5', 'Boris walked over to the window and reflected on his industrial surroundings...');