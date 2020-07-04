void* (*GetHead)(void* player) = (void*(*)(void*))getAbsoluteAddress(il2cppName,0xBA86FC);

void* (*GetHipTF)(void* player) = (void*(*)(void*))getAbsoluteAddress(il2cppName,0xBA8828);

void* (*CurrentMatch)() = (void*(*)())getAbsoluteAddress(il2cppName,0x2689FF4); //static QG CurrentMatch()

void* (*GetLocalPlayer)(void* match) = (void*(*)(void *))getAbsoluteAddress(il2cppName,0xFC2E68); //public Player ^djkVy()

void* (*getPlayerByIndex)(void* match, uint8_t index) = (void*(*)(void *, uint8_t))getAbsoluteAddress(il2cppName,0xFC3308); //public Player |`pUJY(byte cA^OZCl)

int (*get_CurHP)(void* player) = (int(*)(void *))getAbsoluteAddress(il2cppName,0xB5B238);

void* (*get_PlayerID)(void* player) = (void*(*)(void *))getAbsoluteAddress(il2cppName,0xB41C70);

void* (*get_NickName)(void* player) = (void*(*)(void *))getAbsoluteAddress(il2cppName,0xB6F574);

bool (*IsVisible)(void* player) = (bool(*)(void *))getAbsoluteAddress(il2cppName,0xB71864);

bool (*IsFiring)(void* player) = (bool(*)(void *))getAbsoluteAddress(il2cppName,0xB51140);

bool (*get_IsSighting)(void* player) = (bool(*)(void *))getAbsoluteAddress(il2cppName,0xB511A0);

bool (*IsLocalPlayer)(void* player) = (bool(*)(void *))getAbsoluteAddress(il2cppName,0xB3F12C);

bool (*IsLocalTeammate)(void* player) = (bool(*)(void *))getAbsoluteAddress(il2cppName,0xB777B4);

bool (*get_IsDieing)(void* player) = (bool(*)(void *))getAbsoluteAddress(il2cppName,0xB4EE34);

bool (*IsCrouching)(void* player) = (bool(*)(void *))getAbsoluteAddress(il2cppName,0xB4D8C8);//att

bool (*get_IsSkyDiving)(void* player) = (bool(*)(void *))getAbsoluteAddress(il2cppName,0xB70FBC);

bool (*get_IsSkyDashing)(void* player) = (bool(*)(void *))getAbsoluteAddress(il2cppName,0xB71378);

bool (*get_IsParachuting)(void* player) = (bool(*)(void *))getAbsoluteAddress(il2cppName,0xB70BB4);

bool (*IsSameTeam)(void* p1, void* p2) = (bool(*)(void*, void*))getAbsoluteAddress(il2cppName,0x268B518);

void (*SetAimRotation)(void* player, Quaternion rotation) = (void(*)(void *, Quaternion))getAbsoluteAddress(il2cppName,0xB6FF70);

void* (*Component_get_transform)(void* comp) = (void*(*)(void *))getAbsoluteAddress(il2cppName,0x2469E50);

Vector3 (*Transform_get_position)(void* trans) = (Vector3(*)(void *))getAbsoluteAddress(il2cppName,0x2A468EC);

Vector3 (*Transform_get_forward)(void* trans) = (Vector3(*)(void *))getAbsoluteAddress(il2cppName,0x2A46FD0);

void* (*get_main)() = (void*(*)())getAbsoluteAddress(il2cppName,0x2465124); // UnityEngine.Camera

void (*ShowPopupMessage)(void* gamescene, void* message, float duration) = (void(*)(void *, void*, float))getAbsoluteAddress(il2cppName,0x1090B8C);

void* UIInGameScene = NULL;

void* (*il2cpp_string_new)(const char* string) = (void*(*)(const char*))getAbsoluteAddress(il2cppName,0x2AB3ED0);

void* (*String_Concat)(void* string1, void* string2, void* string3) = (void*(*)(void*,void*, void*))getAbsoluteAddress(il2cppName,0x1F44FB4);

int (*Screen_get_width)() = (int(*)())getAbsoluteAddress(il2cppName,0x278E250);

int (*Screen_get_height)() = (int(*)())getAbsoluteAddress(il2cppName,0x278E2E0);

Vector3 (*WorldToScreenPoint)(void* camera, Vector3 position) = (Vector3 (*)(void*, Vector3)) getAbsoluteAddress(il2cppName,0x2464B34);








class Rect {
public:
    float x;
    float y;
    float width;
    float height;

    Rect(float x, float y, float width, float height){
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }
};

class Color {
public:
    float r;
    float g;
    float b;
    float a;

    Color(float r, float g, float b, float a){
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
};

Vector3 GetHeadPosition(void* player){
    return Transform_get_position(*(void**) ((uint64_t) player + 0x18C));
}

Vector3 GetHipPosition(void* player){
    return Transform_get_position(*(void**) ((uint64_t) player + 0x190));
}
void* GetClosestEnemy(void* match, bool byFOV) {
    if(!match) {
        return NULL;
    }

    float shortestDistance = 99999;
    float maxAngle = 30.0;
    void* closestEnemy = NULL;
    void* LocalPlayer = GetLocalPlayer(match);

    if(LocalPlayer && !get_IsSkyDashing(LocalPlayer) && !get_IsParachuting(LocalPlayer) && !get_IsSkyDiving(LocalPlayer) && !get_IsDieing(LocalPlayer)) {
        for(int u = 0; u <= 50; u++) {
            void* Player = getPlayerByIndex(match, (uint8_t)u);
            if(Player && !IsLocalPlayer(Player) && !IsLocalTeammate(Player) && !get_IsDieing(Player) && !get_IsSkyDashing(Player) && !get_IsParachuting(Player) &&
               !get_IsSkyDiving(Player) && IsVisible(Player) && get_CurHP(Player) > 0)
            {
                Vector3 PlayerPos = GetHipPosition(Player);
                Vector3 LocalPlayerPos = GetHipPosition(LocalPlayer);//Transform_get_position(Component_get_transform(get_main()));
                float distanceToMe = Vector3::Distance(LocalPlayerPos, PlayerPos);

                if(byFOV) {
                    Vector3 targetDir = PlayerPos - LocalPlayerPos;
                    float angle = Vector3::Angle(targetDir, Transform_get_forward(Component_get_transform(get_main()))) * 100.0;
                    if(angle <= maxAngle) {
                        if(distanceToMe < shortestDistance) {
                            shortestDistance = distanceToMe;
                            closestEnemy = Player;
                        }
                    }
                } else {
                    if(distanceToMe < shortestDistance) {
                        shortestDistance = distanceToMe;
                        closestEnemy = Player;
                    }
                }
            }
        }
    }
    return closestEnemy;
}


void (*Update)(void* gamestartup); //GameStartup
void _Update(void* gamestartup) {
    if(Update) {
        void* Match = CurrentMatch();
        if((aimbot || fireaimbot || scopeaimbot || espdistance || squataimbot ) && Match) {
            void* LocalPlayer = GetLocalPlayer(Match);

            if(LocalPlayer){

                //ESP
                if(espdistance && UIInGameScene){
                    for(int u = 0; u < 100; u++) {
                        void* Player = getPlayerByIndex(Match, (uint8_t)u);
                        if(Player && !IsLocalPlayer(Player) && !get_IsDieing(Player) && IsVisible(Player) && get_CurHP(Player) > 0) {
                            Vector3 PlayerPos = GetHeadPosition(Player);
                            Vector3 LocalPos = Transform_get_position(Component_get_transform(get_main()));

                            char dist[10];
                            float n = Vector3::Distance(LocalPos, PlayerPos);
                            sprintf(dist, " Metros", (int)n);
                            //ShowPopupMessage(UIInGameScene, String_Concat(*(void**) ((uint64_t) Player + 0xA8), il2cpp_string_new_0(dist)), 2.0);

                            int i = 0;
                            void* headtf = *(void**) ((uint64_t) Player + 0x154);
                            if(headtf){
                                Vector3 headpos = WorldToScreenPoint(get_main(), Transform_get_position(headtf));

                                int screenWidth = Screen_get_width();
                                int screenHeight = Screen_get_height();

                                Vector2 from = Vector2((screenWidth / 2), screenHeight);
                                Vector2 to = Vector2(headpos.X, screenHeight - headpos.Y);


                            }
                        }
                    }
                }
                

                
                //Aimbot
                void* closestEnemy = GetClosestEnemy(Match, aimbot);
                if(closestEnemy) {
                    Vector3 PlayerPos = GetHeadPosition(closestEnemy);
                    Vector3 LocalPos = Transform_get_position(Component_get_transform(get_main()));
                    Vector3 up = Vector3::Up();
                    Vector3 b = Vector3::Zero();

                    if(IsCrouching(closestEnemy)) {
                        b = Vector3::Down() * 0.4;
                    }

                    Vector3 Forward = PlayerPos - LocalPos + (up * 0.3) + b;
                    if(cabeca) {
                        Forward = GetHeadPosition(closestEnemy) - LocalPos + b;
 }
                    if(espdistance && UIInGameScene) {
                        char dist[10];
                        float n = Vector3::Distance(GetHipPosition(LocalPlayer), PlayerPos);
                        sprintf(dist, " Metros", (int)n);
                        ShowPopupMessage(UIInGameScene, String_Concat(NULL, get_NickName(closestEnemy), il2cpp_string_new(dist)), 2.0);
                    }

                    Quaternion lookRotation = Quaternion::LookRotation(Forward, up);
                    if((scopeaimbot && get_IsSighting(LocalPlayer))) {
                        SetAimRotation(LocalPlayer, lookRotation);
                    } else if(fireaimbot && IsFiring(LocalPlayer)) {
                        SetAimRotation(LocalPlayer, lookRotation);
                    } else if(aimbot) {
                        SetAimRotation(LocalPlayer, lookRotation);
                    } else if(squataimbot && IsCrouching(LocalPlayer)) {
                        SetAimRotation(LocalPlayer, lookRotation);
                    }
                }
            }
        }
    }
    Update(gamestartup);
}

void (*OnInit)(void* gamescene); // COW.UIInGameScene
void _OnInit(void* gamescene) {
    OnInit(gamescene);
    if(gamescene) {
        UIInGameScene = gamescene;
    }
}