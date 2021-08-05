function $(_el){
    return document.querySelector(_el);
}

onload=preLoad;


class SoundPool{
    constructor(auds=[]){
        this.aud=auds;
        this.loaded=0;
        this.playingIndex=0;
        this.isPlaying=0;
        this.aud.forEach(function(aud){
            aud.aud.oncanplaythrough=this.onLoadStep.bind(this);
            if(aud.aud.loop){
                aud.loop=true;
            }
        }.bind(this));
        
        this.onLoadComplete=Math.random;
    }
    add(aud,name){
        this.aud.push({'aud':aud,'name':name}); //no event listeners :P
    }
    onLoadStep(){
        $('#loadLog').innerHTML+='[+] SOUND : '+this.aud[this.loaded].name+'  LOADED SUCCESSFULLY!  <br>';
        this.loaded++;
        if(this.loaded==this.aud.length){
            this.onLoadComplete();
            this.onLoadComplete=Math.random;
        }
    }
    play(name){
        if(!name){
            this.isPlaying=true;
            this.aud[this.playingIndex].aud.play();
        }
        for(let i=0;i<this.aud.length;i++){
            if(this.aud[i].name == name){
                this.playingIndex=i;
                this.aud[this.playingIndex].aud.play();
            }
        }
    }
    pause(name){
        if(!name){
            this.isPlaying=true;
            this.aud[this.playingIndex].aud.play();
        }
        for(let i=0;i<this.aud.length;i++){
            if(this.aud[i].name == name){
                this.playingIndex=i;
                this.aud[this.playingIndex].aud.pause();
            }
        }
    }
}

let sp;

function preLoad(){
    let SOUNDS=[
        {
            'aud':new Audio('./assets/bgm.mp3'),
            'name':'bgm',
            'loop':true,
        },
        // {
        //     // 'aud':new Audio('./assets/crazy.mp3'),
        //     // 'name':'crazy'
        // },
    ];

    sp=new SoundPool(SOUNDS);
    sp.onLoadComplete=main;
}

function main(){
        
    setTimeout(init,5000); //just to make user wait xD
}

function init(){
    $('#loader').style.display="none";
    $('#main').classList.add('show');
}
function initGame(){
    $('#main').classList.remove('show');
    $('#GameArea').classList.add('show');    
    $('#vid').play();
    sp.play('bgm');
    
    let w=$('#vid').videoWidth;
    let h=$('#vid').videoHeight;
    let ar=w/h;
    h=innerHeight;
    if(w>=innerWidth && h>=innerHeight){
    w=ar*innerHeight;
        $('#vid').style.height=h+"px";
        $('#vid').style.width=w+"px";
        
    }else{
        ar=h/w;
        $('#vid').style.width=(innerWidth)+"px";
        $('#vid').style.height=ar*(innerWidth)+"px";
    }
    
}
function skipIntro(){   
    $('#vid').style.display='none';
    $('#boo').style.display='block';
    $('#skpIntro').style.display='none';
    sp.pause('bgm');

    $('#boo').play();
    $('#boo').onended=final;
    let w=$('#boo').videoWidth;
    let h=$('#boo').videoHeight;
    let ar=w/h;
    h=innerHeight;
    w=ar*innerHeight;
    if(w>=innerWidth && h>=innerHeight){
        $('#boo').style.height=h+"px";
        $('#boo').style.width=w+"px";
        //$('#boo').style.transform="translate(-50%,0%)";
    }else{
        ar=h/w;
        
        //$('#boo').style.transform="translate(0%,-25%)";
        $('#boo').style.width=(innerWidth)+"px";
        $('#boo').style.height=ar*(innerWidth)+"px";
    }
}

function final(){
    $("#GameArea").innerHTML="<span>😂😂😂😂 </span><br><br> <h1>Dont Worry!<br> I Wont Say This To Anyone...</h1>";
}
