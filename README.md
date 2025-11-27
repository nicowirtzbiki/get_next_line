## Descrição

`get_next_line` devolve a próxima linha disponível no fluxo associado a um **descritor de ficheiro** (ficheiro, STDIN, socket, pipe, …). Cada chamada lê o que for necessário do FD, acumula em memória e retorna exatamente **uma linha**, **incluindo o `\n` final** quando existente. Ao chegar ao EOF sem `\n`, devolve a última linha sem `\n`.

> Este comportamento segue os requisitos típicos do projeto 42 _get_next_line_, incluindo o uso de variável(‑eis) estática(s) para manter estado entre chamadas.

### Contratos da função

- **Entrada**: `fd` válido e aberto para leitura.
- **Saída**: ponteiro para _string_ alocada com a próxima linha lida do `fd`.
- **Formato da linha**:

  - Se a linha no ficheiro termina com `\n`, a _string_ devolvida **inclui** esse `\n`.
  - Na última linha, se o ficheiro termina em EOF sem `\n`, a _string_ **não** inclui `\n`.

- **Persistência**: entre chamadas, o estado não consumido mantém-se em memória (estático) para concluir linhas seguintes.

### Erros e retorno

- **`NULL`** se:

  - `fd` é inválido;
  - ocorre erro em `read(2)`;
  - não há mais dados a ler (EOF) **e** não existe conteúdo por devolver.

- Em caso de sucesso, retorna uma _string_ alocada (depois o utilizador deve chamar `free()`).

---

- declarar buffer e inicializar ele comzeeros (porque..)
- declarar static
