<template>
  <v-container>
    <v-card
      rounded="xl"
      color="#FFFFFF"
      elevation="10"
      max-width="1000px"
      class="bigrect-home"
    >
      <v-row>
        <v-col cols="4" class="hometext">
          <v-container>
            <v-row justify-md>
              <v-img
                class="logo"
                src="https://cdn.discordapp.com/attachments/691762837457993788/1033767650054123551/study-icon-78591_1.png"
                max-height="110px"
                max-width="110px"
              ></v-img>
            </v-row>
            <v-row>
              <v-divider intern class="divider-home"></v-divider>
            </v-row>
            <v-row>
              <v-btn
                depressed
                elevation="0"
                large
                plain
                width="192px"
                class="align-button-home"
                @click="go_to_path('/login')"
              >
                <b>Login</b>
              </v-btn>
            </v-row>
            <v-row>
              <v-divider intern class="divider-home"></v-divider>
            </v-row>
            <v-row>
              <v-btn
                depressed
                elevation="0"
                large
                plain
                width="192px"
                class="align-button-home"
                @click="go_to_path('/user')"
              >
                <b>Perfil</b>
              </v-btn>
            </v-row>
            <v-row>
              <v-divider intern class="divider-home"></v-divider>
            </v-row>
            <v-row>
              <v-btn
                depressed
                elevation="0"
                large
                plain
                width="192px"
                class="align-button-home"
                @click="go_to_path('/registergroup')"
              >
                <b>Criar Grupo</b>
              </v-btn>
            </v-row>
            <v-row>
              <v-divider intern class="divider-home"></v-divider>
            </v-row>
            <v-row>
              <v-btn
                depressed
                elevation="0"
                large
                plain
                width="192px"
                class="align-button-home"
                @click="go_to_path('/search')"
              >
                <b>Procurar Grupo</b>
              </v-btn>
            </v-row>
            <v-row>
              <v-divider intern class="divider-home"></v-divider>
            </v-row>
            <v-row>
              <v-btn
                depressed
                elevation="0"
                large
                plain
                width="192px"
                class="align-button-home"
              >
                <b>Meu Grupo</b>
              </v-btn>
            </v-row>
            <v-row>
              <v-divider intern class="divider-home"></v-divider>
            </v-row>
          </v-container>
        </v-col>
        <v-col cols="1">
          <v-divider vertical></v-divider>
        </v-col>
        <v-col cols="7" class="hometext">
          <b class="welcome">Bem-vindo,</b>
          <br>
          O Study Hall se trata de uma plataforma que permite que você possa se conectar a outras pessoas com o mesmo propósito: Estudo em grupo!
          <br>
          <br>
          Nosso objetivo é fazer com que você possa achar grupos de estudos que estejam alinhados com os assuntos e matérias que você tem interesse em estudar! Você pode achar grupos de estudos de todo o mundo ou focar em achar pessoas da sua cidade, tudo para que você tenha uma experiência personalizada.
          <br>
          <br>
          Para que você possa aproveitar por completo tudo que nossa plataforma pode te oferecer, pedimos que realize um cadastro ou, caso já seja um membro, que você faça login com suas credenciais.
        </v-col>
      </v-row>
    </v-card>
  </v-container>
</template>
<script>
export default {
  methods: {
    go_to_path (path) {
      if (this.$route.path !== path) {
        this.$router.push(path);
      }
    }
  },
}
</script>
<style>
.hometext {
  border-right: 60px solid transparent;
  border-left: 15px solid transparent;
  border-top: 10px solid transparent;
  border-bottom: 10px solid transparent;
  text-align: justify;
  text-justify: inter-word;
}

.welcome {
  border-right: 60px solid transparent;
  border-left: 15px solid transparent;
  border-top: 10px solid transparent;
  border-bottom: 10px solid transparent;
  text-align: justify;
  text-justify: inter-word;
  font-size: 60px;
}

.bigrect-home {
  margin-top: 30px;
  margin-bottom: 20px;
  margin-left: 70px;
}

.logo {
  margin-top: 10px;
  margin-left: 90px;
  margin-bottom: 20px;
}

.divider-home {
  margin-left: 50px;
}

.align-button-home {
  margin-left: 50px;
}
</style>
