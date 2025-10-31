# Meu Projeto

Este projeto é uma aplicação web construída com TypeScript e Express. Abaixo estão as informações sobre a estrutura do projeto e suas funcionalidades.

## Estrutura do Projeto

```
meu-projeto
├── src
│   ├── app.ts               # Ponto de entrada da aplicação
│   ├── controllers
│   │   └── index.ts         # Controlador principal da aplicação
│   ├── routes
│   │   └── index.ts         # Configuração das rotas
│   └── types
│       └── index.ts         # Tipos personalizados para a aplicação
├── package.json              # Configuração do npm
├── tsconfig.json             # Configuração do TypeScript
└── README.md                 # Documentação do projeto
```

## Funcionalidades

- **src/app.ts**: Cria uma instância do aplicativo Express e configura middleware e rotas.
- **src/controllers/index.ts**: Exporta a classe `IndexController` com o método `getIndex` para lidar com a rota raiz.
- **src/routes/index.ts**: Exporta a função `setRoutes` que configura as rotas utilizando o `IndexController`.
- **src/types/index.ts**: Exporta interfaces `Request` e `Response` que estendem as interfaces da biblioteca `express`.
- **tsconfig.json**: Define as opções do compilador TypeScript e os arquivos a serem incluídos na compilação.
- **package.json**: Lista as dependências e scripts do projeto.

## Como Executar

1. Clone o repositório.
2. Instale as dependências com `npm install`.
3. Compile o projeto com `tsc`.
4. Execute a aplicação com `node dist/app.js`.

## Contribuição

Sinta-se à vontade para contribuir com melhorias ou correções. Abra uma issue ou um pull request!