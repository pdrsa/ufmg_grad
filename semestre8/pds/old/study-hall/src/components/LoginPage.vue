<template>
  <v-container>
    <v-card
      rounded="xl"
      color="#FFFFFF"
      elevation="10"
      max-width="800px"
      height="450px"
      class="bigrect-login"
    >

      <v-row>
        <v-spacer></v-spacer>
        <h1 class="pa-8">Login</h1>
        <v-spacer></v-spacer>
      </v-row>

      <v-row>
      <v-spacer></v-spacer>
        <v-text-field
        v-model="username"
        label="Username"
        ref="username"
        filled
        clearable
        dense
        rounded
        >
        </v-text-field>
      <v-spacer></v-spacer>
      </v-row>
      <v-row>
      <v-spacer></v-spacer>
        <v-text-field
        v-model="password"
        label="Password"
        ref="password"
        filled
        clearable
        rounded
        type="password"
        >
        </v-text-field>
      <v-spacer></v-spacer>
      </v-row>
      <v-row>
      <v-spacer></v-spacer>
        <v-btn
          depressed
          elevation="2"
          large
          width="192px"
          color="blue"
          class="align-button-login"
          @click="login"
        >
          <b>Login</b>
        </v-btn>
      <v-spacer></v-spacer>
        <v-btn
          depressed
          elevation="2"
          large
          color="blue"
          width="192px"
          class="align-button-login"
          @click="go_to_path('/register')"
        >
          <b>Register</b>
        </v-btn>
      <v-spacer></v-spacer>
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
    },
    login(){
      alert(this.username + ":" + this.password)
    }
  },
}
</script>
<style>
.bigrect-login {
  margin-top: 30px;
  margin-bottom: 20px;
  margin-left: 170px;
}

.align-button-login {
  margin-top: 80px;
}

</style>
