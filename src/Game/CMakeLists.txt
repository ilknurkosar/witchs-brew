target_include_directories(${PROJECT_NAME} PRIVATE
    include
)
target_sources(${PROJECT_NAME} PRIVATE
    Customer.cpp
    DayGui.cpp
    DayTime.cpp
    Item.cpp
    Inventory.cpp
    NightGui.cpp
    NightTime.cpp
    PotionShop.cpp
    TradeAgent.cpp
    InfiniteShop.cpp
)