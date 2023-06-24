<template>
    <v-container>
      <v-card
        color="#FFFFFF"
        elevation=2
        height="1400px"
        width="1188px"
        rounded="xl"
        class="bigrect"
      >
        <div>
            <v-row>
                <v-col
                class="searchtext" >
                    <h1>Filtros</h1>
                </v-col>

                <v-col
                class="searchfilter">
                    <v-select
                    :items="filtros"
                    filled
                    rounded
                    label="Filtro 1"
                    style="width:200px"
                    ></v-select>
                </v-col>

            </v-row>

            <v-row>
              <v-divider intern class="divider"></v-divider>
            </v-row>

            <v-row
                v-for="(item) in toRender" :key="item.title"
                class="groupcards"
            >
                    <v-card
                        :color="item.color"
                        dark
                        height="200px"
                        width="1000px"
                    >
                      <v-row>
                        <v-column>
                          <v-img :src="item.src"
                          height="150px"
                          width="150px"
                          class="cardimage"
                          ></v-img>
                        </v-column>
                        <v-row>
                          <v-column>
                            <h2 class="cardcontent">{{ item.title }}</h2>
                          </v-column>

                          <v-column>
                            <h2 class="cardcontent">Membros:</h2>
                          </v-column>
                        </v-row>
                      </v-row>
                    </v-card>
            </v-row>
            <v-row>
              <v-divider intern class="divider"></v-divider>
            </v-row>

            <v-row>
                <v-btn @click="loadnext()" class="nextbutton">next</v-btn>
            </v-row>
        </div>
      </v-card>
    </v-container>
  </template>
  
  <script>
    export default {
        data: () => ({
            filtros: ['Foo', 'Bar', 'Fizz', 'Buzz'],
            items: [
                {
                color: '#1F7087',
                src: 'https://cdn.vuetifyjs.com/images/cards/foster.jpg',
                title: 'Supermodel',
                artist: 'Foster the People',
                },
                {
                color: '#952175',
                src: 'https://cdn.vuetifyjs.com/images/cards/halcyon.png',
                title: 'Halcyon Days',
                artist: 'Ellie Goulding',
                },
                {
                color: '#952175',
                src: 'https://cdn.vuetifyjs.com/images/cards/halcyon.png',
                title: 'Halcyon Days',
                artist: 'Ellie Goulding',
                },
                {
                color: '#952175',
                src: 'https://cdn.vuetifyjs.com/images/cards/halcyon.png',
                title: 'Halcyon Days',
                artist: 'Ellie Goulding',
                },
                {
                color: '#952175',
                src: 'https://cdn.vuetifyjs.com/images/cards/halcyon.png',
                title: 'Halcyon Days',
                artist: 'Ellie Goulding',
                },
                {
                color: '#952175',
                src: 'https://cdn.vuetifyjs.com/images/cards/halcyon.png',
                title: 'Halcyon Days',
                artist: 'Ellie Goulding',
                },
            ],
            start: 0, // Lower limit 
            end: 5, // Upper Limit
            questions: [], // Array containing all the questions.
            toRender: []
        }),

        mounted() {
            for (let i = this.start; i < this.end; i++){
                this.toRender.push(this.items[i])
            }
            this.start = this.start + this.toRender.length
            this.end = this.items.length
        },

        methods: {
            loadnext() {
              this.toRender = [];
              for (let i = this.start; i < (this.start + 5); i++){
                  if (i >= this.end) {
                    break;
                  }
                  this.toRender.push(this.items[i])
              }
            }
        } 
    }
  </script>

  <style>
  .searchtext {
    border-right: 70px solid transparent;
    border-left: 70px solid transparent;
    border-top: 50px solid transparent;
  }

  .searchfilter {
    border-right: 0px solid transparent;
    border-left: 30px solid transparent;
    border-top: 50px solid transparent;
  }

  .groupcards {
    border-right: 70px solid transparent;
    border-left: 70px solid transparent;
    border-top: 20px solid transparent;
  }
  
  .buttonregister {
    background-color: #0D1A8F;
    color: white;
  }
  
  .bigrect {
    margin-top: 30px;
    margin-bottom: 20px;
    margin-left: -5px;
  }
  
  .uploading-image{
       display:flex;
     }

  .divider {
      margin-top: 15px;
      margin-left: 50px;
      margin-right: 50px;
  }

  .cardimage {
    margin-top: 30px;
    margin-left: 50px;
    margin-right: 50px;
  }

  .cardcontent {
    margin-top: 50px;
    margin-left: 50px;
    margin-right: 50px;
    margin-bottom: 50px;
  }

  .nextbutton {
    margin-top: 50px;
    margin-left: 50px;
    margin-right: 50px;
    margin-bottom: 50px;
  }
  </style>
  
