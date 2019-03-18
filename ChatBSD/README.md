# ChatBSD
Chat realizat cu BSD Sockets, pentru proiect PAD.
Echipa ce se ocupa de proiect este alcatuita din:
  Miron Florin
  Utica Raian
  Nenad Srbovan
  Milea Darius
Proiectul nostru este:
Program care ofera o camera de discutii mai multor utilizatori.

Componente:
  - server concurent
  - client

Server:

Gestioneaza o camera de chat acceptand mai multe conexiuni simultane de la
utilizatorii care vor sa discute. Utilizatorii trebuie sa se autentifice
printr-un nume si o parola. Numele trebuie sa fie unice.

Serverul va primi mesaje de la utilizatorii conectati si va trimite imediat
tuturor clientilor mesajele primite.

Client

Se conecteaza la server si ofera utilizatorului o interfata text prin care
poate sa trimita mesaje spre camera de discutii. Un mesaj trimis de
un utilizator va aparea simultan in interfata oferita tuturor 
utilizatorilor, inclusiv a celui care a scris initial mesajul.

Documentatie disponibila:
http://labs.cs.upt.ro/labs/sprc/html/res/sockets.pdf
http://labs.cs.upt.ro/labs/sprc/html/sockets.html
http://labs.cs.upt.ro/labs/sprc/html/res/Designing%20a%20Protocol.pdf
