# NCC-GameMachine
Menu gráfico para seleção e execução de jogos das NCC GameMachines do Núcleo de Ciência de Computação (NCC) da Universidade Federal de Santa Maria (UFSN)

## Equipe de Desenvolvimento
 * [Cassiano Schneider](https://github.com/cassiandrei)
 * [Lucas Ferreira](https://github.com/LucasFerreiraDaSilva)
 * [Rafael Trindade](https://github.com/648trindade)
 * [Viníciu Dreifke](https://github.com/Vinniekun)

## Objetivo
Incentivar alunos dos cursos de Informática da UFSM a realizarem o desenvolvmento de jogos _open-source_, buscando trazer motivação para a busca de conhecimento extra-classe, gosto por programação e apreço por **Software Livre**.

Como objetivo secundário destaca-se a revitalização de máquinas caça-níqueis apreendidas há muitos anos pelo governo federal que estão localizadas nas dependências do NCC, literalmente mofando. 

Originalmente, dispunham somente de seu corpo (madeira), um monitor de tubo, botões e um display LED. O projeto visa revitalizar essas máquinas com um conjunto relativamente novo de:

 * **Hardware**: Novos somente em consideração à idade dos caça-níqueis. A idéia de reciclar _hardware_ velho serve também como desafio para os alunos desenvolverem jogos de maneira eficiente.
    * Placas-mãe velhas serão reutilizads, munidas de processadores defasados no mercado, como Intel Pentium 4; 
    * Monitor de tubo 20 polegadas; 
    * Conjunto de botões de fliperama + manche; 
    * Circuito interno de um joystick genérico;
 * **Software**:
    * Sistema Debian Buster, munido de servidor gráfico (X), porém sem _Windows Manager_, _Desktop Manager_ ou _Desktop Environment_;
    * **Este software** - Menu gráfico para a seleção de jogos
    * Jogos: Os mais diversos jogos criados pelos alunos da UFSM

## Jogos
Esse repositório não conterá os jogos criados pelos alunos. Entretanto, é possível conferir um modelo de configuração de diretório para um jogo dentro da pasta games. O jogo usado como exemplo é o jogo [**SuperTux**](http://supertux.org), e não encontra-se fisicamente nesse repositório: recomenda-se a instalação via apt-get no sistema alvo (`apt install supertux`)

## Sobre esta aplicação
Deixamos a licença GPL 3 nela. Então sinta-se livre pra clonar e modificar a seu próprio gosto, caso sinta vontade.
Ela está sendo desenvolvida em C++11, com a biblioteca de renderização **SDL 2**.
Há o aproveitamento de trechos de código da engine criada pelo [Tim Jones](http://SDLTutorials.com) e um _header_ que possibilita a leitura de arquivos json, de [Nield Lohmann](https://github.com/nlohmann/json).

## Links úteis
[Site da UFSM](http://ufsm.br)
[Site da Informática UFSM](http://www.inf.ufsm.br)
[Wiki do Informática UFSM](http://wiki.inf.ufsm.br/)
